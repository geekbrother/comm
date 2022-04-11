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
  EXPECT_EQ(item.getSign(), foundItem->getSign());
  database::DatabaseManager::getInstance().removeSessionSignItem(
      item.getDeviceID());
}
