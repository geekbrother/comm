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

TEST_F(DatabaseManagerTest, TestOperationsOnMessageFindByReceiver) {
  const std::string receiverID =
      "mobile:EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm";
  const database::MessageItem item(
      "bc0c1aa2-bf09-11ec-9d64-0242ac120002",
      "mobile:EMQNoQ7b2ueEmQ4QsevRWlXxFCNt055y20T1PHdoYAQRt0S6TLzZWNM6XSvdWqxm",
      receiverID,
      "lYlNcO6RR4i9UW3G1DGjdJTRRGbqtPya2aj94ZRjIGZWoHwT5MB9ciAgnQf2VafYb9Tl"
      "8SZkX37tg4yZ9pOb4lqslY4g4h58OmWjumghVRvrPUZDalUuK8OLs1Qoengpu9wccxAk"
      "Bti2leDTNeiJDy36NnwS9aCIUc0ozsMvXfX1gWdBdmKbiRG1LvpNd6S7BNGG7Zly5zYj"
      "xz7s6ZUSDoFfZe3eJWQ15ngYhgMw1TsfbECnMVQTYvY6OyqWPBQi5wiftFcluoxor8G5"
      "RJ1NEDQq2q2FRfWjNHLhky92C2C7Nnfe4oVzSinfC1319uUkNLpSzI4MvEMi6g5Ukbl7"
      "iGhpnX7Hp4xpBL3h2IkvGviDRQ98UvW0ugwUuPxm1NOQpjLG5dPoqQ0jrMst0Bl5rgPw"
      "ajjNGsUWmp9r0ST0wRQXrQcY30PoSoqKSlCEgFMLzHWLrPQ86QFyCICismGSe7iBIqdD"
      "6d37StvXBzfJoZVU79UeOF2bFvb3DNoArEOe",
      "7s6ZUSDoFfZe3eJWQ15ngYhgMw1TsfbECnMVQTYvY6OyqWPBQi5wiftFcluoxor8",
      static_cast<uint64_t>(std::time(0)) + 600);
  EXPECT_EQ(
      database::DatabaseManager::getInstance().isTableAvailable(
          item.getTableName()),
      true);
  database::DatabaseManager::getInstance().putMessageItem(item);
  std::vector<std::shared_ptr<database::MessageItem>> foundItems =
      database::DatabaseManager::getInstance().findMessageItemsByReceiver(
          receiverID);
  EXPECT_NE(foundItems.size(), 0);
  EXPECT_EQ(item.getFromDeviceID(), foundItems[0]->getFromDeviceID());
  EXPECT_EQ(item.getToDeviceID(), foundItems[0]->getToDeviceID());
  EXPECT_EQ(item.getPayload(), foundItems[0]->getPayload());
  EXPECT_EQ(item.getBlobHashes(), foundItems[0]->getBlobHashes());
  EXPECT_EQ(item.getExpire(), foundItems[0]->getExpire());
  database::DatabaseManager::getInstance().removeMessageItem(
      item.getMessageID());
}
