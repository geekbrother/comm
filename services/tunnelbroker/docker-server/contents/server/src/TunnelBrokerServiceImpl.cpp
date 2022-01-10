#pragma once

#include "TunnelBrokerServiceImpl.h"
#include "AwsTools.h"
#include "DatabaseManager.h"
#include "Tools.h"

#include <folly/stop_watch.h>
#include <chrono>
#include <iostream>
#include <memory>
namespace comm {
namespace network {

using namespace std::chrono_literals;

TunnelBrokerServiceImpl()::TunnelBrokerServiceImpl()() {
  Aws::InitAPI({});
}

TunnelBrokerServiceImpl::~TunnelBrokerServiceImpl() {
  Aws::ShutdownAPI({});
}

grpc::Status TunnelBrokerServiceImpl::CheckIfPrimaryDeviceOnline(
    grpc::ServerContext *context,
    const tunnelbroker::CheckRequest *request,
    tunnelbroker::CheckResponse *response) {
  const std::string id = request->userid();
  const std::string deviceToken = request->devicetoken();

  auto iterator = primaries.find(id);

  if (iterator == primaries.end()) {
    response->set_checkresponsetype(
        tunnelbroker::CheckResponseType::PRIMARY_DOESNT_EXIST);
  } else if (deviceToken == iterator->second->deviceToken) {
    response->set_checkresponsetype(
        tunnelbroker::CheckResponseType::CURRENT_IS_PRIMARY);
  } else {
    // TODO: the background notif should be sent what cannot be really
    // simulated here I believe
    iterator->second->pingRequests.blockingWrite(true);
    // TODO: timeout currently set for 3s, to be changed
    const auto wait = std::chrono::seconds(3);
    folly::stop_watch<> watch;
    bool isActive;
    bool responseReceived = iterator->second->pingResponses.tryReadUntil(
        watch.getCheckpoint() + wait, isActive);
    if (responseReceived) {
      iterator->second->lastState = ping::ClientState::ONLINE;
      response->set_checkresponsetype(
          tunnelbroker::CheckResponseType::PRIMARY_ONLINE);
    } else {
      iterator->second->lastState = ping::ClientState::OFFLINE;
      response->set_checkresponsetype(
          tunnelbroker::CheckResponseType::PRIMARY_OFFLINE);
    }
  }

  return grpc::Status::OK;
}

grpc::Status TunnelBrokerServiceImpl::BecomeNewPrimaryDevice(
    grpc::ServerContext *context,
    const tunnelbroker::NewPrimaryRequest *request,
    tunnelbroker::NewPrimaryResponse *response) {
  const std::string id = request->userid();
  const std::string deviceToken = request->devicetoken();

  std::shared_ptr<ping::ClientData> clientData =
      std::make_shared<ping::ClientData>(id, deviceToken);
  auto iterator = primaries.find(id);
  if (iterator == primaries.end()) {
    primaries.insert_or_assign(id, clientData);
    response->set_success(true);
    return grpc::Status::OK;
  }
  if (iterator->second->deviceToken == deviceToken) {
    response->set_success(true);
    return grpc::Status::OK;
  }

  if (iterator->second->lastState == ping::ClientState::ONLINE) {
    response->set_success(false);
  } else {
    primaries.insert_or_assign(id, clientData);
    response->set_success(true);
  }

  return grpc::Status::OK;
}

grpc::Status TunnelBrokerServiceImpl::SendPong(
    grpc::ServerContext *context,
    const tunnelbroker::PongRequest *request,
    google::protobuf::Empty *response) {
  const std::string id = request->userid();
  const std::string deviceToken = request->devicetoken();

  auto iterator = primaries.find(id);

  if (iterator == primaries.end() ||
      iterator->second->deviceToken != deviceToken) {
    return grpc::Status::OK;
  }

  if (!iterator->second->pingRequests.isEmpty()) {
    bool value;
    iterator->second->pingRequests.blockingRead(value);
    iterator->second->pingResponses.write(true);
  }

  return grpc::Status::OK;
}

grpc::Status TunnelBrokerServiceImpl::NewSession(
    grpc::ServerContext *context,
    const tunnelbroker::NewSessionRequest *request,
    grpc::ServerWriter<tunnelbroker::NewSessionResponse> *writer) {
  tunnelbroker::NewSessionRequest request;
  tunnelbroker::NewSessionResponse response;
  std::shared_ptr<database::DeviceSessionItem> deviceSessionItem;
  const std::string deviceId = request->deviceId();
  const std::string userId = request->userId();
  const std::string notifyToken = request->notifyToken();
  const std::string typeOs = request->typeOs();
  const std::string sessionId = randomString(SESSION_ID_LENGTH);
  try {
    // need to add check if the session already exist to the database maanger
    // and return status error.
    deviceSessionItem = std::make_shared<database::DeviceSessionItem>(
        sessionId, deviceId, userId, notifyToken, typeOs);
    database::DatabaseManager::getInstance().putSessionItem(*deviceSessionItem);
  } catch (std::runtime_error &e) {
    std::cout << "Error while processing NewSession request: " << e.what()
              << std::endl;
    return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
  }
  return grpc::Status::OK;
}

grpc::Status TunnelBrokerServiceImpl::Send(
    grpc::ServerContext *context,
    const tunnelbroker::SendRequest *request,
    grpc::ServerWriter<tunnelbroker::SendResponse> *writer) {
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
