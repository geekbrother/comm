#include "AmqpManager.h"
#include "ConfigManager.h"
#include "Constants.h"
#include "DeliveryBroker.h"
#include "Tools.h"

#include <gtest/gtest.h>

#include <string>
#include <thread>

using namespace comm::network;

class DatabaseManagerTest : public testing::Test {
protected:
  virtual void SetUp() {
    config::ConfigManager::getInstance().load();
    std::thread amqpThread([]() { AmqpManager::getInstance().connect(); });
  }
};

TEST_F(DatabaseManagerTest, TestOperationsOnSendAndReceive) {
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
