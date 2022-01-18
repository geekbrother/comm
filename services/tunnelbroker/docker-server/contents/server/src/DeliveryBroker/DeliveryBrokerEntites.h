#pragma once

#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace comm {
namespace network {

struct DeliveryBrokerMessageStruct {
  std::string fromDeviceID;
  std::string payload;
  std::vector<std::string> blobHashes;
};

std::mutex DeliveryBroker_m;
std::unordered_map<std::string, std::vector<DeliveryBrokerMessageStruct>>
    DeliveryBrokerMessage_map;

} // namespace network
} // namespace comm
