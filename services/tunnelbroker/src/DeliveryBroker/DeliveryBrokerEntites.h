#pragma once

#include <folly/concurrency/UnboundedQueue.h>

#include <string>
#include <vector>

namespace comm {
namespace network {

struct DeliveryBrokerMessage {
  std::string messageID;
  uint64_t deliveryTag;
  std::string fromDeviceID;
  std::string payload;
  std::vector<std::string> blobHashes;
};

typedef folly::UMPMCQueue<DeliveryBrokerMessage, true> DeliveryBrokerQueue;

} // namespace network
} // namespace comm
