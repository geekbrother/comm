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
      "bc0c1aa2-bf09-11ec-9d64-0242ac120002",
      "mobile:EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm",
      "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC9Q9wodsQdZNynbTnC35hA4mFW"
      "mwZf9BhbI93aGAwPF9au0eYsawRz0jtYi4lSFXC9KleyQDg+6J+UW1kiWvE3ZRYG"
      "ECqgx4zqajPTzVt7EAOGaIh/dPyQ6x2Ul1GlkkSYXUhhixEzExGp9g84eCyVkbCB"
      "U3SK6SNKyR7anAXDVQIDAQAB",
      "hbI93aGAwPF9au0eYsawRz0jtYi4lSFXC9KleyQDg+6J+UW1kiWvE3",
      "phone",
      "ios:1.1.1",
      "iOS 99.99.99");
  EXPECT_EQ(
      database::DatabaseManager::getInstance().isTableAvailable(
          item.getTableName()),
      true);
  database::DatabaseManager::getInstance().putSessionItem(item);
  std::shared_ptr<database::DeviceSessionItem> foundItem =
      database::DatabaseManager::getInstance().findSessionItem(
          item.getSessionID());
  EXPECT_NE(foundItem, nullptr);
  EXPECT_EQ(item.getDeviceID(), foundItem->getDeviceID());
  EXPECT_EQ(item.getPubKey(), foundItem->getPubKey());
  EXPECT_EQ(item.getNotifyToken(), foundItem->getNotifyToken());
  EXPECT_EQ(item.getDeviceType(), foundItem->getDeviceType());
  EXPECT_EQ(item.getAppVersion(), foundItem->getAppVersion());
  EXPECT_EQ(item.getDeviceOs(), foundItem->getDeviceOs());
  database::DatabaseManager::getInstance().removeSessionItem(
      item.getSessionID());
}

TEST_F(DatabaseManagerTest, TestOperationsOnDeviceSessionItemGenerated) {
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
  EXPECT_EQ(item.getDeviceID(), foundItem->getDeviceID())
      << "Generated DeviceID \"" << item.getDeviceID()
      << "\" differs from what is found in the database "
      << foundItem->getDeviceID();
  EXPECT_EQ(item.getPubKey(), foundItem->getPubKey())
      << "Generated PubKey \"" << item.getPubKey()
      << "\" differs from what is found in the database "
      << foundItem->getPubKey();
  EXPECT_EQ(item.getNotifyToken(), foundItem->getNotifyToken())
      << "Generated NotifyToken \"" << item.getNotifyToken()
      << "\" differs from what is found in the database "
      << foundItem->getNotifyToken();
  EXPECT_EQ(item.getDeviceType(), foundItem->getDeviceType())
      << "Generated DeviceType \"" << item.getDeviceType()
      << "\" differs from what is found in the database "
      << foundItem->getDeviceType();
  EXPECT_EQ(item.getAppVersion(), foundItem->getAppVersion())
      << "Generated AppVersion \"" << item.getAppVersion()
      << "\" differs from what is found in the database "
      << foundItem->getAppVersion();
  EXPECT_EQ(item.getDeviceOs(), foundItem->getDeviceOs())
      << "Generated DeviceOS \"" << item.getDeviceOs()
      << "\" differs from what is found in the database "
      << foundItem->getDeviceOs();
  database::DatabaseManager::getInstance().removeSessionItem(
      item.getSessionID());
}
