#pragma once

#include <folly/concurrency/ConcurrentHashMap.h>

#include <string>
#include <vector>

namespace comm {
namespace network {

struct DeliveryBrokerMessageStruct {
  std::string fromDeviceID;
  std::string payload;
  std::vector<std::string> blobHashes;
};

typedef folly::
    ConcurrentHashMap<std::string, std::vector<DeliveryBrokerMessageStruct>>
        DeliveryBrokerHashmapType;

} // namespace network
} // namespace comm
