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

public:
  TunnelBrokerServiceImpl();
  virtual ~TunnelBrokerServiceImpl();

  // Create new session method
  grpc::Status NewSession(
      grpc::ServerContext *context,
      const tunnelbroker::NewSessionRequest *request,
      tunnelbroker::NewSessionResponse *reply) override;

  // Send message to deviceID method
  grpc::Status Send(
      grpc::ServerContext *context,
      const tunnelbroker::SendRequest *request,
      google::protobuf::Empty *reply) override;

  // Get messages for the deviceID from the queue as stream
  grpc::Status
  Get(grpc::ServerContext *context,
      const tunnelbroker::GetRequest *request,
      grpc::ServerWriter<tunnelbroker::GetResponse> *stream) override;
};

} // namespace network
} // namespace comm
