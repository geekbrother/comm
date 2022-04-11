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
