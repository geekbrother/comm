#pragma once

#include <amqpcpp.h>
#include <amqpcpp/libuv.h>

#include <atomic>
#include <memory>
#include <string>

namespace comm {
namespace network {
namespace amqp {

class AmqpManager {
  std::unique_ptr<AMQP::TcpChannel> amqpChannel;
  std::atomic<bool> amqpReady;
  long long lastConnectionTimestamp;
  void connectInternal();

public:
  static AmqpManager &getInstance();
  void connect();
  bool
  send(std::string toDeviceID, std::string fromDeviceID, std::string payload);
  void ack(uint64_t deliveryTag);
};

} // namespace amqp
} // namespace network
} // namespace comm
