#include "TunnelbrokerServiceImpl.h"

#include "AmqpManager.h"
#include "AwsTools.h"
#include "Constants.h"
#include "DatabaseManager.h"
#include "DeliveryBroker.h"
#include "Tools.h"

namespace comm {
namespace network {

using namespace std::chrono_literals;

TunnelBrokerServiceImpl::TunnelBrokerServiceImpl() {
  Aws::InitAPI({});
  if (!database::DatabaseManager::getInstance().isAvailable()) {
    throw std::runtime_error(
        "Error: AWS DynamoDB table '" + DEVICE_SESSIONS_TABLE_NAME +
        "' is not available.");
  }
}

TunnelBrokerServiceImpl::~TunnelBrokerServiceImpl() {
  Aws::ShutdownAPI({});
}

grpc::Status TunnelBrokerServiceImpl::SessionSignature(
    grpc::ServerContext *context,
    const tunnelbroker::SessionSignatureRequest *request,
    tunnelbroker::SessionSignatureResponse *reply) {

  const std::string toSign = generateRandomString(SIGNATURE_REQUEST_LENGTH);
  reply->set_tosign(toSign);
  return grpc::Status::OK;
}

grpc::Status TunnelBrokerServiceImpl::NewSession(
    grpc::ServerContext *context,
    const tunnelbroker::NewSessionRequest *request,
    tunnelbroker::NewSessionResponse *reply) {

  std::shared_ptr<database::DeviceSessionItem> deviceSessionItem;
  const std::string sessionId = generateRandomString(SESSION_ID_LENGTH);
  try {
    if (database::DatabaseManager::getInstance().findSessionItem(sessionId) !=
        nullptr) {
      std::cout << "gRPC: "
                << "Session " << sessionId << " already exist." << std::endl;
      return grpc::Status(
          grpc::StatusCode::ALREADY_EXISTS, "Session already exist.");
    }
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
  reply->set_sessionid(sessionId);
  return grpc::Status::OK;
}

grpc::Status TunnelBrokerServiceImpl::Send(
    grpc::ServerContext *context,
    const tunnelbroker::SendRequest *request,
    google::protobuf::Empty *reply) {

  try {
    const std::string sessionId = request->sessionid();
    // Check if the sessionId from request exists in DB
    // or return PERMISSION_DENIED.
    std::shared_ptr<database::DeviceSessionItem> sessionItem =
        database::DatabaseManager::getInstance().findSessionItem(sessionId);
    if (sessionItem == nullptr) {
      std::cout << "gRPC: "
                << "Session " << sessionId << " not found." << std::endl;
      return grpc::Status(
          grpc::StatusCode::PERMISSION_DENIED,
          "No such session found. SessionId: " + sessionId);
    }
    const std::string clientDeviceId = sessionItem->getDeviceId();
    if (!AMQPSend(
            request->todeviceid(),
            clientDeviceId,
            std::string(request->payload()))) {
      std::cout << "gRPC: "
                << "Error while publish the message to AMQP" << std::endl;
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
    // Check if the sessionId from request exists in DB
    // or return PERMISSION_DENIED.
    std::shared_ptr<database::DeviceSessionItem> sessionItem =
        database::DatabaseManager::getInstance().findSessionItem(sessionId);
    if (sessionItem == nullptr) {
      std::cout << "gRPC: "
                << "Session " << sessionId << " not found." << std::endl;
      return grpc::Status(
          grpc::StatusCode::PERMISSION_DENIED,
          "No such session found. SessionId: " + sessionId);
    }
    const std::string clientDeviceId = sessionItem->getDeviceId();
    // Check if the DeliveryBroker queue is not empty for the deviceID and
    // deliver the messages by the gRPC stream message responses if not
    std::vector<DeliveryBrokerMessageStruct> messagesToDeliver;
    while (1) {
      if (DeliveryBrokerIsEmpty(clientDeviceId)) {
        continue;
      }
      messagesToDeliver = DeliveryBrokerGet(clientDeviceId);
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
      DeliveryBrokerRemove(clientDeviceId);
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
