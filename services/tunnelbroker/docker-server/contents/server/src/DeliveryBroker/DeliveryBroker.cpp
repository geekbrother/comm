#include "DeliveryBroker.h"

void DeliveryBrokerPush(
    std::string toDeviceID,
    std::string fromDeviceID,
    std::string payload) {
  std::unique_lock<decltype(DeliveryBroker_m)> lock(DeliveryBroker_m);
  // TODO: Add updating of the vector in the hashmap key.
};

std::vector<DeliveryBrokerMessageStruct>
DeliveryBrokerGet(std::string deviceID) {
  std::unique_lock<decltype(DeliveryBroker_m)> lock(DeliveryBroker_m);
  return DeliveryBrokerMessage_map[deviceID];
};
