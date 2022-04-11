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
  EXPECT_EQ(item.getDeviceID(), foundItem->getDeviceID());
  EXPECT_EQ(item.getPubKey(), foundItem->getPubKey());
  EXPECT_EQ(item.getNotifyToken(), foundItem->getNotifyToken());
  EXPECT_EQ(item.getDeviceType(), foundItem->getDeviceType());
  EXPECT_EQ(item.getAppVersion(), foundItem->getAppVersion());
  EXPECT_EQ(item.getDeviceOs(), foundItem->getDeviceOs());
  database::DatabaseManager::getInstance().removeSessionItem(
      item.getSessionID());
}
