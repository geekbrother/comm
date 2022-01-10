#pragma once

#include <memory>
#include <string>

#include <folly/concurrency/ConcurrentHashMap.h>

#include <grpcpp/grpcpp.h>

#include "../_generated/tunnelbroker.grpc.pb.h"
#include "../_generated/tunnelbroker.pb.h"

#include "Tools.h"

namespace comm {
namespace network {

class TunnelBrokerServiceImpl final
    : public tunnelbroker::TunnelBrokerService::Service {
  folly::ConcurrentHashMap<std::string, std::shared_ptr<ping::ClientData>>
      primaries;

public:
  TunnelBrokerServiceImpl();
  virtual ~TunnelBrokerServiceImpl();

  // Testing methods
  grpc::Status CheckIfPrimaryDeviceOnline(
      grpc::ServerContext *context,
      const tunnelbroker::CheckRequest *request,
      tunnelbroker::CheckResponse *response) override;
  grpc::Status BecomeNewPrimaryDevice(
      grpc::ServerContext *context,
      const tunnelbroker::NewPrimaryRequest *request,
      tunnelbroker::NewPrimaryResponse *response) override;
  grpc::Status SendPong(
      grpc::ServerContext *context,
      const tunnelbroker::PongRequest *request,
      google::protobuf::Empty *response) override;

  // Create new session method
  grpc::Status NewSession(
      grpc::ServerContext *context,
      const tunnelbroker::NewSessionRequest *request,
      grpc::ServerWriter<tunnelbroker::NewSessionResponse> *writer) override;

  // Send message to deviceID method
  grpc::Status Send(
      grpc::ServerContext *context,
      const tunnelbroker::SendRequest *request,
      grpc::ServerWriter<tunnelbroker::SendResponse> *writer) override;

  // Get messages for the deviceID from the queue as stream
  grpc::Status
  Get(grpc::ServerContext *context,
      const tunnelbroker::GetRequest *request,
      grpc::ServerWriter<tunnelbroker::GetResponse> *stream) override;
};

} // namespace network
} // namespace comm
