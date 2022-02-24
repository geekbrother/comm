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
    std::unique_lock<std::mutex> localLock(this->localMutex);
    std::unordered_map<std::string, DeliveryBrokerMessage> messagesList;
    const DeliveryBrokerMessage newMessage = {
        .deliveryTag = deliveryTag,
        .fromDeviceID = fromDeviceID,
        .payload = payload};

    if (this->messagesMap.find(toDeviceID) == this->messagesMap.end()) {
      messagesList[messageID] = newMessage;
      this->messagesMap.insert({toDeviceID, messagesList});
      this->localCv.notify_all();
      return;
    }

    messagesList = this->messagesMap[toDeviceID];
    messagesList[messageID] = newMessage;
    this->messagesMap.assign(toDeviceID, messagesList);
    this->localCv.notify_all();
  } catch (const std::exception &e) {
    std::cout << "DeliveryBroker push: "
              << "Got an exception " << e.what() << std::endl;
    this->localCv.notify_all();
  }
};

std::unordered_map<std::string, DeliveryBrokerMessage>
DeliveryBroker::get(const std::string deviceID) {
  if (this->messagesMap.find(deviceID) == this->messagesMap.end()) {
    return {};
  }
  return this->messagesMap[deviceID];
};

bool DeliveryBroker::isEmpty(const std::string deviceID) {
  if (this->messagesMap.empty()) {
    return true;
  }
  return (this->messagesMap.find(deviceID) == this->messagesMap.end());
};

void DeliveryBroker::remove(
    const std::string deviceID,
    const std::string messageID) {
  try {
    std::unique_lock<std::mutex> localLock(this->localMutex);
    std::unordered_map<std::string, DeliveryBrokerMessage> messagesList;
    if (this->messagesMap.find(deviceID) == this->messagesMap.end()) {
      return;
    }
    messagesList = this->messagesMap[deviceID];
    messagesList.erase(messageID);
    this->messagesMap.assign(deviceID, messagesList);
    this->localCv.notify_all();
  } catch (const std::exception &e) {
    std::cout << "DeliveryBroker remove: "
              << "Got an exception " << e.what() << std::endl;
    this->localCv.notify_all();
  }
}

void DeliveryBroker::erase(const std::string deviceID) {
  this->messagesMap.erase(deviceID);
};

void DeliveryBroker::wait(const std::string deviceID) {
  std::unique_lock<std::mutex> localLock(this->localMutex);
  this->localCv.wait(
      localLock, [this, &deviceID] { return !this->isEmpty(deviceID); });
};

} // namespace network
} // namespace comm
