#include "DeliveryBroker.h"

namespace comm {
namespace network {

DeliveryBroker &DeliveryBroker::getInstance() {
  static DeliveryBroker instance;
  return instance;
};

void DeliveryBroker::push(
    const std::string messageID,
    const uint64_t deliveryTag,
    const std::string toDeviceID,
    const std::string fromDeviceID,
    const std::string payload) {
  try {

    const DeliveryBrokerMessage newMessage = {
        .messageID = messageID,
        .deliveryTag = deliveryTag,
        .fromDeviceID = fromDeviceID,
        .payload = payload};

    if (this->messagesMap.find(toDeviceID) == this->messagesMap.end()) {
      this->messagesMap.insert(
          toDeviceID,
          std::make_unique<folly::MPMCQueue<DeliveryBrokerMessage>>(100));
    }
    *(this->messagesMap).find(toDeviceID)->second->blockingWrite(newMessage);
  } catch (const std::exception &e) {
    std::cout << "DeliveryBroker push: "
              << "Got an exception " << e.what() << std::endl;
  }
};

bool DeliveryBroker::isEmpty(const std::string deviceID) {
  if (this->messagesMap.empty()) {
    return true;
  }
  return (this->messagesMap.find(deviceID) == this->messagesMap.end());
};

DeliveryBrokerMessage DeliveryBroker::pop(const std::string deviceID) {
  try {
    DeliveryBrokerMessage message;
    if (this->messagesMap.find(deviceID) == this->messagesMap.end()) {
      return message;
    }
    *(this->messagesMap).find(deviceID)->second->blockingRead(message);
    return message;
  } catch (const std::exception &e) {
    std::cout << "DeliveryBroker remove: "
              << "Got an exception " << e.what() << std::endl;
  }
}

void DeliveryBroker::erase(const std::string deviceID) {
  this->messagesMap.erase(deviceID);
};

} // namespace network
} // namespace comm
