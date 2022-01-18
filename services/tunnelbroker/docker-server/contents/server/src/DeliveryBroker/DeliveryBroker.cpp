#include "DeliveryBroker.h"

namespace comm {
namespace network {

DeliveryBroker &DeliveryBroker::getInstance() {
  static DeliveryBroker instance;
  return instance;
};

void DeliveryBroker::push(
    const std::string toDeviceID,
    const std::string fromDeviceID,
    const std::string payload) {
  std::unique_lock<std::mutex> localLock(localMutex);
  std::vector<DeliveryBrokerMessage> messagesList;
  const DeliveryBrokerMessage newMessage = {
      .fromDeviceID = fromDeviceID, .payload = payload};

  if (messagesMap.find(toDeviceID) == messagesMap.end()) {
    messagesList.push_back(newMessage);
    messagesMap.insert({toDeviceID, messagesList});
    localCv.notify_all();
    return;
  }

  messagesList = messagesMap[toDeviceID];
  messagesList.push_back(newMessage);
  messagesMap.assign(toDeviceID, messagesList);
  localCv.notify_all();
};

std::vector<DeliveryBrokerMessage>
DeliveryBroker::get(const std::string deviceID) {
  if (messagesMap.find(deviceID) == messagesMap.end()) {
    return {};
  }
  return messagesMap[deviceID];
};

bool DeliveryBroker::isEmpty(const std::string key) {
  if (messagesMap.empty()) {
    return true;
  }
  if (messagesMap.find(key) == messagesMap.end()) {
    return true;
  }
  return false;
};

void DeliveryBroker::remove(const std::string key) {
  messagesMap.erase(key);
};

void DeliveryBroker::wait(const std::string key) {
  std::unique_lock<std::mutex> localLock(localMutex);
  localCv.wait(localLock, [this, &key] { return !isEmpty(key); });
};

} // namespace network
} // namespace comm
