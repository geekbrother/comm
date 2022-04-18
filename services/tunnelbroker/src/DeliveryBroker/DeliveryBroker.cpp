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
    if (this->messagesMap.find(toDeviceID) == this->messagesMap.end()) {
      this->messagesMap.insert(
          toDeviceID, std::make_unique<DeliveryBrokerQueue>());
    }
    if (this->messagesMap.find(toDeviceID)->second->size() >=
        DELIVERY_BROKER_MAX_QUEUE_SIZE) {
      throw std::runtime_error(
          "DeliveryBroker messages queue size for deviceID " + toDeviceID +
          " is greater than " + std::to_string(DELIVERY_BROKER_MAX_QUEUE_SIZE));
    }
    this->messagesMap.find(toDeviceID)
        ->second->enqueue(DeliveryBrokerMessage{
            .messageID = messageID,
            .deliveryTag = deliveryTag,
            .fromDeviceID = fromDeviceID,
            .payload = payload});
  } catch (const std::exception &e) {
    std::cout << "DeliveryBroker push: "
              << "Got an exception " << e.what() << std::endl;
  }
};

bool DeliveryBroker::isEmpty(const std::string deviceID) {
  if (this->messagesMap.find(deviceID) == this->messagesMap.end()) {
    return true;
  };
  return this->messagesMap.find(deviceID)->second->empty();
};

DeliveryBrokerMessage DeliveryBroker::pop(const std::string deviceID) {
  try {
    // If we don't already have a queue insert it for the blocking read purpose
    // in case we listen first before the insert happens.
    if (this->messagesMap.find(deviceID) == this->messagesMap.end()) {
      this->messagesMap.insert(
          deviceID, std::make_unique<DeliveryBrokerQueue>());
    }
    return this->messagesMap.find(deviceID)->second->dequeue();
  } catch (const std::exception &e) {
    std::cout << "DeliveryBroker pop: "
              << "Got an exception " << e.what() << std::endl;
  }
  return {};
};

void DeliveryBroker::erase(const std::string deviceID) {
  this->messagesMap.erase(deviceID);
};

} // namespace network
} // namespace comm
