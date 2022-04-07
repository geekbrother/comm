#include "DatabaseManager.h"
#include "ConfigManager.h"
#include "Constants.h"
#include "Tools.h"

#include <gtest/gtest.h>

#include <ctime>
#include <memory>
#include <string>

using namespace comm::network;

class DatabaseManagerTest : public testing::Test {
protected:
  virtual void SetUp() {
    config::ConfigManager::getInstance().load();
    Aws::InitAPI({});
  }

  virtual void TearDown() {
    Aws::ShutdownAPI({});
  }
};

TEST_F(DatabaseManagerTest, TestOperationsOnDeviceSessionItem) {
  const database::DeviceSessionItem item(
      tools::generateUUID(),
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH),
      tools::generateRandomString(451),
      tools::generateRandomString(64),
      tools::generateRandomString(12),
      tools::generateRandomString(12),
      tools::generateRandomString(12));
  EXPECT_EQ(
      database::DatabaseManager::getInstance().isTableAvailable(
          item.getTableName()),
      true);
  database::DatabaseManager::getInstance().putSessionItem(item);
  std::shared_ptr<database::DeviceSessionItem> foundItem =
      database::DatabaseManager::getInstance().findSessionItem(
          item.getSessionID());
  EXPECT_NE(foundItem, nullptr);
  EXPECT_EQ(
      memcmp(
          item.getDeviceID().data(),
          foundItem->getDeviceID().data(),
          item.getDeviceID().size()),
      0);
  EXPECT_EQ(
      memcmp(
          item.getPubKey().data(),
          foundItem->getPubKey().data(),
          item.getPubKey().size()),
      0);
  EXPECT_EQ(
      memcmp(
          item.getNotifyToken().data(),
          foundItem->getNotifyToken().data(),
          item.getNotifyToken().size()),
      0);
  EXPECT_EQ(
      memcmp(
          item.getDeviceType().data(),
          foundItem->getDeviceType().data(),
          item.getDeviceType().size()),
      0);
  EXPECT_EQ(
      memcmp(
          item.getAppVersion().data(),
          foundItem->getAppVersion().data(),
          item.getAppVersion().size()),
      0);
  EXPECT_EQ(
      memcmp(
          item.getDeviceOs().data(),
          foundItem->getDeviceOs().data(),
          item.getDeviceOs().size()),
      0);
  database::DatabaseManager::getInstance().removeSessionItem(
      item.getSessionID());
}

TEST_F(DatabaseManagerTest, TestOperationsOnSessionSignItem) {
  const database::SessionSignItem item(
      tools::generateRandomString(SIGNATURE_REQUEST_LENGTH),
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH));
  EXPECT_EQ(
      database::DatabaseManager::getInstance().isTableAvailable(
          item.getTableName()),
      true);
  database::DatabaseManager::getInstance().putSessionSignItem(item);
  std::shared_ptr<database::SessionSignItem> foundItem =
      database::DatabaseManager::getInstance().findSessionSignItem(
          item.getDeviceID());
  EXPECT_NE(foundItem, nullptr);
  EXPECT_EQ(
      memcmp(
          item.getSign().data(),
          foundItem->getSign().data(),
          item.getSign().size()),
      0);
  database::DatabaseManager::getInstance().removeSessionSignItem(
      item.getDeviceID());
}

TEST_F(DatabaseManagerTest, TestOperationsOnPublicKeyItem) {
  const database::PublicKeyItem item(
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH),
      tools::generateRandomString(451));
  EXPECT_EQ(
      database::DatabaseManager::getInstance().isTableAvailable(
          item.getTableName()),
      true);
  database::DatabaseManager::getInstance().putPublicKeyItem(item);
  std::shared_ptr<database::PublicKeyItem> foundItem =
      database::DatabaseManager::getInstance().findPublicKeyItem(
          item.getDeviceID());
  EXPECT_NE(foundItem, nullptr);
  EXPECT_EQ(
      memcmp(
          item.getPublicKey().data(),
          foundItem->getPublicKey().data(),
          item.getPublicKey().size()),
      0);
  database::DatabaseManager::getInstance().removePublicKeyItem(
      item.getDeviceID());
}

TEST_F(DatabaseManagerTest, TestOperationsOnMessageItem) {
  const database::MessageItem item(
      tools::generateUUID(),
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH),
      "mobile:" + tools::generateRandomString(DEVICEID_CHAR_LENGTH),
      tools::generateRandomString(256),
      tools::generateRandomString(256),
      static_cast<uint64_t>(std::time(0)) + 600);
  EXPECT_EQ(
      database::DatabaseManager::getInstance().isTableAvailable(
          item.getTableName()),
      true);
  database::DatabaseManager::getInstance().putMessageItem(item);
  std::shared_ptr<database::MessageItem> foundItem =
      database::DatabaseManager::getInstance().findMessageItem(
          item.getMessageID());
  EXPECT_NE(foundItem, nullptr);
  EXPECT_EQ(
      memcmp(
          item.getFromDeviceID().data(),
          foundItem->getFromDeviceID().data(),
          item.getFromDeviceID().size()),
      0);
  EXPECT_EQ(
      memcmp(
          item.getToDeviceID().data(),
          foundItem->getToDeviceID().data(),
          item.getToDeviceID().size()),
      0);
  EXPECT_EQ(
      memcmp(
          item.getPayload().data(),
          foundItem->getPayload().data(),
          item.getPayload().size()),
      0);
  EXPECT_EQ(
      memcmp(
          item.getBlobHashes().data(),
          foundItem->getBlobHashes().data(),
          item.getBlobHashes().size()),
      0);
  EXPECT_EQ(item.getExpire() == foundItem->getExpire(), true);
  database::DatabaseManager::getInstance().removeMessageItem(
      item.getMessageID());
}
