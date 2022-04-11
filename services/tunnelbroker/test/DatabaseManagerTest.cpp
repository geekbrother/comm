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

TEST_F(DatabaseManagerTest, TestOperationsOnPublicKeyItem) {
  const database::PublicKeyItem item(
      "mobile:EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm",
      "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC9Q9wodsQdZNynbTnC35hA4mFW"
      "mwZf9BhbI93aGAwPF9au0eYsawRz0jtYi4lSFXC9KleyQDg+6J+UW1kiWvE3ZRYG"
      "ECqgx4zqajPTzVt7EAOGaIh/dPyQ6x2Ul1GlkkSYXUhhixEzExGp9g84eCyVkbCB"
      "U3SK6SNKyR7anAXDVQIDAQAB");
  EXPECT_EQ(
      database::DatabaseManager::getInstance().isTableAvailable(
          item.getTableName()),
      true);
  database::DatabaseManager::getInstance().putPublicKeyItem(item);
  std::shared_ptr<database::PublicKeyItem> foundItem =
      database::DatabaseManager::getInstance().findPublicKeyItem(
          item.getDeviceID());
  EXPECT_NE(foundItem, nullptr);
  EXPECT_EQ(item.getPublicKey(), foundItem->getPublicKey());
  database::DatabaseManager::getInstance().removePublicKeyItem(
      item.getDeviceID());
}

TEST_F(DatabaseManagerTest, TestOperationsOnPublicKeyItemGenerated) {
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
  EXPECT_EQ(item.getPublicKey(), foundItem->getPublicKey())
      << "Generated PublicKey \"" << item.getPublicKey()
      << "\" differs from what is found in the database "
      << foundItem->getPublicKey();
  database::DatabaseManager::getInstance().removePublicKeyItem(
      item.getDeviceID());
}
