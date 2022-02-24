#pragma once

#include "Constants.h"
#include "DeliveryBrokerEntites.h"

#include <folly/concurrency/ConcurrentHashMap.h>

#include <condition_variable>
#include <iostream>
#include <string>
#include <unordered_map>

namespace comm {
namespace network {

class DeliveryBroker {

  folly::ConcurrentHashMap<
      std::string,
      std::unordered_map<std::string, DeliveryBrokerMessage>>
      messagesMap;
  std::mutex localMutex;
  std::condition_variable localCv;

public:
  static DeliveryBroker &getInstance();
  void push(
      const std::string messageID,
      const uint64_t deliveryTag,
      const std::string toDeviceID,
      const std::string fromDeviceID,
      const std::string payload);
  std::unordered_map<std::string, DeliveryBrokerMessage>
  get(const std::string deviceID);
  bool isEmpty(const std::string deviceID);
  void remove(const std::string deviceID, const std::string messageID);
  void erase(const std::string deviceID);
  void wait(const std::string deviceID);
};

} // namespace network
} // namespace comm
