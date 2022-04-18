#include "DeliveryBroker.h"
#include "Tools.h"

#include <gtest/gtest.h>

#include <ctime>
#include <string>

using namespace comm::network;

class DeliveryBrokerTest : public testing::Test {};

TEST(DeliveryBrokerTest, TestOperationsOnPushAndPop) {
  const std::string toDeviceID =
      "mobile:EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm";
  const DeliveryBrokerMessage message{
      .messageID = "bc0c1aa2-bf09-11ec-9d64-0242ac120002",
      .deliveryTag = 99,
      .fromDeviceID =
          "mobile:"
          "uTfNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdooLkRt0S6TLzZWNM6XSvdWLop",
      .payload =
          "lYlNcO6RR4i9UW3G1DGjdJTRRGbqtPya2aj94ZRjIGZWoHwT5MB9ciAgnQf2VafYb9Tl"
          "8SZkX37tg4yZ9pOb4lqslY4g4h58OmWjumghVRvrPUZDalUuK8OLs1Qoengpu9wccxAk"
          "Bti2leDTNeiJDy36NnwS9aCIUc0ozsMvXfX1gWdBdmKbiRG1LvpNd6S7BNGG7Zly5zYj"
          "xz7s6ZUSDoFfZe3eJWQ15ngYhgMw1TsfbECnMVQTYvY6OyqWPBQi5wiftFcluoxor8G5"
          "RJ1NEDQq2q2FRfWjNHLhky92C2C7Nnfe4oVzSinfC1319uUkNLpSzI4MvEMi6g5Ukbl7"
          "iGhpnX7Hp4xpBL3h2IkvGviDRQ98UvW0ugwUuPxm1NOQpjLG5dPoqQ0jrMst0Bl5rgPw"
          "ajjNGsUWmp9r0ST0wRQXrQcY30PoSoqKSlCEgFMLzHWLrPQ86QFyCICismGSe7iBIqdD"
          "6d37StvXBzfJoZVU79UeOF2bFvb3DNoArEOe"};
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

TEST(DeliveryBrokerTest, TestOperationsOnPushAndPopGenerated) {
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

TEST(DeliveryBrokerTest, TestOperationsOnIsEmpty) {
  const std::string deviceID =
      "mobile:"
      "EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm";
  EXPECT_EQ(DeliveryBroker::getInstance().isEmpty(deviceID), true);
  const DeliveryBrokerMessage message{
      .messageID = "bc0c1aa2-bf09-11ec-9d64-0242ac120002",
      .deliveryTag = 99,
      .fromDeviceID =
          "mobile:"
          "uTfNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdooLkRt0S6TLzZWNM6XSvdWLop",
      .payload =
          "lYlNcO6RR4i9UW3G1DGjdJTRRGbqtPya2aj94ZRjIGZWoHwT5MB9ciAgnQf2VafYb9Tl"
          "8SZkX37tg4yZ9pOb4lqslY4g4h58OmWjumghVRvrPUZDalUuK8OLs1Qoengpu9wccxAk"
          "Bti2leDTNeiJDy36NnwS9aCIUc0ozsMvXfX1gWdBdmKbiRG1LvpNd6S7BNGG7Zly5zYj"
          "xz7s6ZUSDoFfZe3eJWQ15ngYhgMw1TsfbECnMVQTYvY6OyqWPBQi5wiftFcluoxor8G5"
          "RJ1NEDQq2q2FRfWjNHLhky92C2C7Nnfe4oVzSinfC1319uUkNLpSzI4MvEMi6g5Ukbl7"
          "iGhpnX7Hp4xpBL3h2IkvGviDRQ98UvW0ugwUuPxm1NOQpjLG5dPoqQ0jrMst0Bl5rgPw"
          "ajjNGsUWmp9r0ST0wRQXrQcY30PoSoqKSlCEgFMLzHWLrPQ86QFyCICismGSe7iBIqdD"
          "6d37StvXBzfJoZVU79UeOF2bFvb3DNoArEOe"};
  DeliveryBroker::getInstance().push(
      message.messageID,
      message.deliveryTag,
      deviceID,
      message.fromDeviceID,
      message.payload);
  EXPECT_EQ(DeliveryBroker::getInstance().isEmpty(deviceID), false);
}

TEST(DeliveryBrokerTest, TestOperationsOnErase) {
  const std::string deviceID =
      "mobile:"
      "EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm";
  const DeliveryBrokerMessage message{
      .messageID = "bc0c1aa2-bf09-11ec-9d64-0242ac120002",
      .deliveryTag = 99,
      .fromDeviceID =
          "mobile:"
          "uTfNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdooLkRt0S6TLzZWNM6XSvdWLop",
      .payload =
          "lYlNcO6RR4i9UW3G1DGjdJTRRGbqtPya2aj94ZRjIGZWoHwT5MB9ciAgnQf2VafYb9Tl"
          "8SZkX37tg4yZ9pOb4lqslY4g4h58OmWjumghVRvrPUZDalUuK8OLs1Qoengpu9wccxAk"
          "Bti2leDTNeiJDy36NnwS9aCIUc0ozsMvXfX1gWdBdmKbiRG1LvpNd6S7BNGG7Zly5zYj"
          "xz7s6ZUSDoFfZe3eJWQ15ngYhgMw1TsfbECnMVQTYvY6OyqWPBQi5wiftFcluoxor8G5"
          "RJ1NEDQq2q2FRfWjNHLhky92C2C7Nnfe4oVzSinfC1319uUkNLpSzI4MvEMi6g5Ukbl7"
          "iGhpnX7Hp4xpBL3h2IkvGviDRQ98UvW0ugwUuPxm1NOQpjLG5dPoqQ0jrMst0Bl5rgPw"
          "ajjNGsUWmp9r0ST0wRQXrQcY30PoSoqKSlCEgFMLzHWLrPQ86QFyCICismGSe7iBIqdD"
          "6d37StvXBzfJoZVU79UeOF2bFvb3DNoArEOe"};
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
