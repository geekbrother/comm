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
