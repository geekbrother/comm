#include "TunnelbrokerServiceImpl.h"

namespace comm {
namespace network {

using namespace std::chrono_literals;

TunnelBrokerServiceImpl::TunnelBrokerServiceImpl() {
  Aws::InitAPI({});
  // Check AWS DynamoDB availability
  if (!database::DatabaseManager::getInstance().isAvailable()) {
    throw std::runtime_error("Error: AWS DynamoDB table check failed.");
  }
}

TunnelBrokerServiceImpl::~TunnelBrokerServiceImpl() {
  Aws::ShutdownAPI({});
}

grpc::Status TunnelBrokerServiceImpl::SessionSignature(
    grpc::ServerContext *context,
    const tunnelbroker::SessionSignatureRequest *request,
    tunnelbroker::SessionSignatureResponse *reply) {
  const std::string deviceID = request->deviceid();
  // Generate new random string to sign request for the deviceID
  const std::string toSign = generateRandomString(SIGNATURE_REQUEST_LENGTH);
  reply->set_tosign(toSign);
  return grpc::Status::OK;
}

grpc::Status TunnelBrokerServiceImpl::NewSession(
    grpc::ServerContext *context,
    const tunnelbroker::NewSessionRequest *request,
    tunnelbroker::NewSessionResponse *reply) {

  const std::string signature = request->signature();
  const std::string pubkey = request->publickey();
  std::shared_ptr<database::DeviceSessionItem> deviceSessionItem;
  // Generate new sessionId from random string
  const std::string sessionId = generateRandomString(SESSION_ID_LENGTH);
  try {
    // Check if a session already exist and throw an error if not
    if (database::DatabaseManager::getInstance().findSessionItem(sessionId) ==
        nullptr) {
      return grpc::Status(
          grpc::StatusCode::ALREADY_EXISTS, "Session already exist.");
    }
    // Insert a new session item to the database
    deviceSessionItem = std::make_shared<database::DeviceSessionItem>(
        sessionId,
        request->deviceid(),
        request->publickey(),
        request->notifytoken(),
        tunnelbroker::NewSessionRequest_DeviceTypes_Name(request->devicetype()),
        request->deviceappversion(),
        request->deviceos());
    database::DatabaseManager::getInstance().putSessionItem(*deviceSessionItem);
  } catch (std::runtime_error &e) {
    std::cout << "gRPC: "
              << "Error while processing NewSession request: " << e.what()
              << std::endl;
    return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  }
  // Send a reply with new sessionId
  reply->set_sessionid(sessionId);
  return grpc::Status::OK;
}

grpc::Status TunnelBrokerServiceImpl::Send(
    grpc::ServerContext *context,
    const tunnelbroker::SendRequest *request,
    google::protobuf::Empty *reply) {

  try {
    const std::string sessionId = request->sessionid();
    // Check if the sessionID from request exists in DB
    // or return PERMISSION_DENIED.
    std::shared_ptr<database::DeviceSessionItem> sessionItem =
        database::DatabaseManager::getInstance().findSessionItem(sessionId);
    if (sessionItem == nullptr) {
      return grpc::Status(
          grpc::StatusCode::PERMISSION_DENIED,
          "No such session found. SessionID: " + sessionId);
    }
    // Publish message to AMQP server
    const std::string clientDeviceID = sessionItem->getDeviceId();
    if (!AMQPSend(
            request->todeviceid(),
            clientDeviceID,
            std::string(request->payload()))) {
      return grpc::Status(
          grpc::StatusCode::INTERNAL,
          "Error while publish the message to AMQP");
    }
  } catch (std::runtime_error &e) {
    std::cout << "gRPC: "
              << "Error while processing Send request: " << e.what()
              << std::endl;
    return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  }
  return grpc::Status::OK;
}

grpc::Status TunnelBrokerServiceImpl::Get(
    grpc::ServerContext *context,
    const tunnelbroker::GetRequest *request,
    grpc::ServerWriter<tunnelbroker::GetResponse> *writer) {

  try {
    const std::string sessionId = request->sessionid();

    // Check if the sessionID from request exists in DB
    // or return PERMISSION_DENIED.
    std::shared_ptr<database::DeviceSessionItem> sessionItem =
        database::DatabaseManager::getInstance().findSessionItem(sessionId);
    if (sessionItem == nullptr) {
      return grpc::Status(
          grpc::StatusCode::PERMISSION_DENIED,
          "No such session found. SessionID: " + sessionId);
    }

    // Check if there are new messages in the local queue to deliver
    const std::string clientDeviceID = sessionItem->getDeviceId();
    std::vector<DeliveryBrokerMessageStruct> messagesToDeliver;

    // Can be refactored to use a better event-based approach.
    // As the gRPC server spawns a new thread for every request we will not
    // block other threads with this.
    while (1) {
      messagesToDeliver = DeliveryBrokerGet(clientDeviceID);
      for (auto const &message : messagesToDeliver) {
        tunnelbroker::GetResponse response;
        response.set_fromdeviceid(message.fromDeviceID);
        response.set_payload(message.payload);
        if (!writer->Write(response)) {
          throw std::runtime_error(
              "gRPC Get handler writer error on sending data.");
        }
      }
      // Remove messages from the queue only after gRPC writer
      DeliveryBrokerRemove(clientDeviceID);
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return grpc::Status::OK;
  } catch (std::runtime_error &e) {
    std::cout << "gRPC: "
              << "Error while processing Get request: " << e.what()
              << std::endl;
    return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  }
  return grpc::Status::OK;
}

} // namespace network
} // namespace comm
