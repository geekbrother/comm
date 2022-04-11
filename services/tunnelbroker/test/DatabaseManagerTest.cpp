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

TEST_F(DatabaseManagerTest, TestOperationsOnSessionSignItem) {
  const database::SessionSignItem item(
      "bB3OSLdKlY60KPBpw6VoGKX7Lmw3SA07FmNhnqnclvVeaxXueAQ0dpQSpiQTtlGn",
      "mobile:EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm";
  EXPECT_EQ(
      database::DatabaseManager::getInstance().isTableAvailable(
          item.getTableName()),
      true);
  database::DatabaseManager::getInstance().putSessionSignItem(item);
  std::shared_ptr<database::SessionSignItem> foundItem =
      database::DatabaseManager::getInstance().findSessionSignItem(
          item.getDeviceID());
  EXPECT_NE(foundItem, nullptr);
  EXPECT_EQ(item.getSign(), foundItem->getSign());
  database::DatabaseManager::getInstance().removeSessionSignItem(
      item.getDeviceID());
}

TEST_F(DatabaseManagerTest, TestOperationsOnSessionSignItemGenerated) {
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
  EXPECT_NE(foundItem, nullptr) << "Item with the key of deviceID \""
                                << item.getDeviceID() << "\" is not found";
  EXPECT_EQ(item.getSign(), foundItem->getSign())
      << "Generated signature value \"" << item.getSign()
      << "\" is not equal of \"" + foundItem->getSign() +
          "\" from the database value";
  database::DatabaseManager::getInstance().removeSessionSignItem(
      item.getDeviceID());
}
