#include "TunnelBrokerServiceImpl.h"
#include "AwsTools.h"
#include "DatabaseManager.h"
#include "Tools.h"

#include <folly/stop_watch.h>
#include <chrono>
#include <iostream>
#include <memory>

#include <random>
#include <string>

std::string randomString(std::size_t length) {
  const std::string CHARACTERS =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

  std::string random_string;

  for (std::size_t i = 0; i < length; ++i) {
    random_string += CHARACTERS[distribution(generator)];
  }

  return random_string;
}
namespace comm {
namespace network {

using namespace std::chrono_literals;

TunnelBrokerServiceImpl::TunnelBrokerServiceImpl() {
  Aws::InitAPI({});
}

TunnelBrokerServiceImpl::~TunnelBrokerServiceImpl() {
  Aws::ShutdownAPI({});
}

grpc::Status TunnelBrokerServiceImpl::NewSession(
    grpc::ServerContext *context,
    const tunnelbroker::NewSessionRequest *request,
    tunnelbroker::NewSessionResponse *reply) {
  std::shared_ptr<database::DeviceSessionItem> deviceSessionItem;
  const std::string sessionId = randomString(SESSION_ID_LENGTH);
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
        request->userid(),
        request->notifytoken(),
        request->typeos());
    database::DatabaseManager::getInstance().putSessionItem(*deviceSessionItem);
  } catch (std::runtime_error &e) {
    std::cout << "Error while processing NewSession request: " << e.what()
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
    // Todo:
    // Send implementation
  } catch (std::runtime_error &e) {
    std::cout << "Error while processing Send request: " << e.what()
              << std::endl;
    return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  }
  return grpc::Status::OK;
}

grpc::Status TunnelBrokerServiceImpl::Get(
    grpc::ServerContext *context,
    const tunnelbroker::GetRequest *request,
    grpc::ServerWriter<tunnelbroker::GetResponse> *stream) {
  try {
    // Todo:
    // Get implementation
  } catch (std::runtime_error &e) {
    std::cout << "Error while processing Get request: " << e.what()
              << std::endl;
    return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  }
  return grpc::Status::OK;
}

} // namespace network
} // namespace comm
