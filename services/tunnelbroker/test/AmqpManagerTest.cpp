#include "AmqpManager.h"
#include "ConfigManager.h"
#include "Constants.h"
#include "DeliveryBroker.h"
#include "Tools.h"

#include <gtest/gtest.h>

#include <string>
#include <thread>

using namespace comm::network;

class AmqpManagerTest : public testing::Test {
protected:
  virtual void SetUp() {
    config::ConfigManager::getInstance().load();
    std::thread amqpThread([]() { AmqpManager::getInstance().connect(); });
  }
};

TEST_F(AmqpManagerTest, TestOperationsOnSendAndReceive) {
  const std::string messageID = "bc0c1aa2-bf09-11ec-9d64-0242ac120002";
  const std::string toDeviceID =
      "mobile:EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm";
  const std::string fromDeviceID =
      "mobile:JouLWf84zqRIsjBdHLOcHS9M4eSCz7VF84wT1uOD83u1qxDAqmqI4swmxNINjuhd";
  const std::string payload =
      "lYlNcO6RR4i9UW3G1DGjdJTRRGbqtPya2aj94ZRjIGZWoHwT5MB9ciAgnQf2VafYb9Tl"
      "8SZkX37tg4yZ9pOb4lqslY4g4h58OmWjumghVRvrPUZDalUuK8OLs1Qoengpu9wccxAk"
      "Bti2leDTNeiJDy36NnwS9aCIUc0ozsMvXfX1gWdBdmKbiRG1LvpNd6S7BNGG7Zly5zYj"
      "xz7s6ZUSDoFfZe3eJWQ15ngYhgMw1TsfbECnMVQTYvY6OyqWPBQi5wiftFcluoxor8G5"
      "RJ1NEDQq2q2FRfWjNHLhky92C2C7Nnfe4oVzSinfC1319uUkNLpSzI4MvEMi6g5Ukbl7"
      "iGhpnX7Hp4xpBL3h2IkvGviDRQ98UvW0ugwUuPxm1NOQpjLG5dPoqQ0jrMst0Bl5rgPw"
      "ajjNGsUWmp9r0ST0wRQXrQcY30PoSoqKSlCEgFMLzHWLrPQ86QFyCICismGSe7iBIqdD"
      "6d37StvXBzfJoZVU79UeOF2bFvb3DNoArEOe";
  EXPECT_EQ(
      AmqpManager::getInstance().send(
          messageID, toDeviceID, fromDeviceID, payload),
      true);
  DeliveryBrokerMessage receivedMessage =
      DeliveryBroker::getInstance().pop(toDeviceID);
  EXPECT_EQ(messageID == receivedMessage.messageID, true);
  EXPECT_EQ(fromDeviceID == receivedMessage.fromDeviceID, true);
  EXPECT_EQ(payload == receivedMessage.payload, true);
  AmqpManager::getInstance().ack(receivedMessage.deliveryTag);
}

TEST_F(AmqpManagerTest, TestOperationsOnSendAndReceiveGenerated) {
  const std::string messageID = tools::generateUUID();
  const std::string toDeviceID =
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH);
  const std::string fromDeviceID =
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH);
  const std::string payload = tools::generateRandomString(512);
  EXPECT_EQ(
      AmqpManager::getInstance().send(
          messageID, toDeviceID, fromDeviceID, payload),
      true);
  DeliveryBrokerMessage receivedMessage =
      DeliveryBroker::getInstance().pop(toDeviceID);
  EXPECT_EQ(messageID == receivedMessage.messageID, true);
  EXPECT_EQ(fromDeviceID == receivedMessage.fromDeviceID, true);
  EXPECT_EQ(payload == receivedMessage.payload, true);
  AmqpManager::getInstance().ack(receivedMessage.deliveryTag);
}
