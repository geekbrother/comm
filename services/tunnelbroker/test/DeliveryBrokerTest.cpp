#include "DeliveryBroker.h"
#include "Tools.h"

#include <gtest/gtest.h>

#include <ctime>
#include <string>

using namespace comm::network;

class DeliveryBrokerTest : public testing::Test {};

TEST_F(DeliveryBrokerTest, TestOperationsOnPushAndPop) {
  const std::string toDeviceID =
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH);
  const DeliveryBrokerMessage message{
      .messageID = tools::generateUUID(),
      .deliveryTag = std::time(0),
      .fromDeviceID =
          "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH),
      .payload = tools::generateRandomString(512)};
  DeliveryBroker::getInstance().push(
      message.messageID,
      message.deliveryTag,
      toDeviceID,
      message.fromDeviceID,
      message.payload);
  DeliveryBrokerMessage receivedMessage =
      DeliveryBroker::getInstance().pop(toDeviceID);
  EXPECT_EQ(message.messageID == receivedMessage.messageID, true);
  EXPECT_EQ(message.deliveryTag == receivedMessage.deliveryTag, true);
  EXPECT_EQ(message.fromDeviceID == receivedMessage.fromDeviceID, true);
  EXPECT_EQ(message.payload == receivedMessage.payload, true);
}

TEST_F(DeliveryBrokerTest, TestOperationsOnIsEmpty) {
  const std::string deviceID =
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH);
  EXPECT_EQ(DeliveryBroker::getInstance().isEmpty(deviceID), true);
  const DeliveryBrokerMessage message{
      .messageID = tools::generateUUID(),
      .deliveryTag = std::time(0),
      .fromDeviceID =
          "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH),
      .payload = tools::generateRandomString(512)};
  DeliveryBroker::getInstance().push(
      message.messageID,
      message.deliveryTag,
      deviceID,
      message.fromDeviceID,
      message.payload);
  EXPECT_EQ(DeliveryBroker::getInstance().isEmpty(deviceID), false);
}

TEST_F(DeliveryBrokerTest, TestOperationsOnErase) {
  const std::string deviceID =
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH);
  const DeliveryBrokerMessage message{
      .messageID = tools::generateUUID(),
      .deliveryTag = std::time(0),
      .fromDeviceID =
          "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH),
      .payload = tools::generateRandomString(512)};
  DeliveryBroker::getInstance().push(
      message.messageID,
      message.deliveryTag,
      deviceID,
      message.fromDeviceID,
      message.payload);
  EXPECT_EQ(DeliveryBroker::getInstance().isEmpty(deviceID), false);
  DeliveryBroker::getInstance().erase(deviceID);
  EXPECT_EQ(DeliveryBroker::getInstance().isEmpty(deviceID), true);
}
