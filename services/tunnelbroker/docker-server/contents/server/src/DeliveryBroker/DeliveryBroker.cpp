#include "DeliveryBroker.h"

namespace comm {
namespace network {

DeliveryBrokerHashmapType deliveryBrokerMessagesMap;

void DeliveryBrokerPush(
    std::string toDeviceID,
    std::string fromDeviceID,
    std::string payload) {
  std::vector<DeliveryBrokerMessageStruct> messagesList;
  const DeliveryBrokerMessageStruct newMessage = {
      .fromDeviceID = fromDeviceID, .payload = payload};
  // If no any record create a new one
  if (deliveryBrokerMessagesMap.find(toDeviceID) ==
      deliveryBrokerMessagesMap.end()) {
    messagesList.push_back(newMessage);
    deliveryBrokerMessagesMap.insert({toDeviceID, messagesList});
    return;
  }
  // Update the messages vector with the new message
  messagesList = deliveryBrokerMessagesMap[toDeviceID];
  messagesList.push_back(newMessage);
  deliveryBrokerMessagesMap.assign(toDeviceID, messagesList);
};

std::vector<DeliveryBrokerMessageStruct>
DeliveryBrokerGet(std::string deviceID) {
  if (deliveryBrokerMessagesMap.find(deviceID) ==
      deliveryBrokerMessagesMap.end()) {
    return {};
  }
  return deliveryBrokerMessagesMap[deviceID];
};

bool DeliveryBrokerIsEmpty(std::string key) {
  if (deliveryBrokerMessagesMap.empty()) {
    return true;
  }
  if (deliveryBrokerMessagesMap.find(key) == deliveryBrokerMessagesMap.end()) {
    return true;
  }
  return false;
}

void DeliveryBrokerRemove(std::string key) {
  deliveryBrokerMessagesMap.erase(key);
};

void DeliveryBrokerClear() {
  deliveryBrokerMessagesMap.clear();
};

} // namespace network
} // namespace comm
