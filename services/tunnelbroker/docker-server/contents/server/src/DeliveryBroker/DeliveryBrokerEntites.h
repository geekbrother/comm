#pragma once

#include <folly/concurrency/ConcurrentHashMap.h>

#include <string>
#include <vector>

namespace comm {
namespace network {

struct DeliveryBrokerMessage {
  std::string fromDeviceID;
  std::string payload;
  std::vector<std::string> blobHashes;
};

} // namespace network
} // namespace comm
