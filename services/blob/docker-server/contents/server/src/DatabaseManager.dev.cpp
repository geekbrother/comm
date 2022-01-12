#include "DatabaseManager.h"
#include "DatabaseSimulator.h"
#include "Tools.h"

#include <iostream>
#include <string>

namespace comm {
namespace network {
namespace database {

DatabaseManager &DatabaseManager::getInstance() {
  static DatabaseManager instance;
  return instance;
}

void DatabaseManager::putBlobItem(const BlobItem &item) {
  std::shared_ptr<BlobItem> blobItem = std::make_shared<BlobItem>(
      item.getBlobHash(), item.getS3Path(), getCurrentTimestamp());
  DatabaseSimulator::getInstance().putItem(
      item.getTableName(), std::move(blobItem));
}

std::shared_ptr<BlobItem>
DatabaseManager::findBlobItem(const std::string &blobHash) {
  std::function<std::shared_ptr<Item>(std::vector<std::shared_ptr<Item>> &)>
      searchCallback = [&blobHash](std::vector<std::shared_ptr<Item>> &items)
      -> std::shared_ptr<Item> {
    for (size_t i = 0; i < items.size(); ++i) {
      if (std::dynamic_pointer_cast<BlobItem>(items.at(i))->getBlobHash() ==
          blobHash) {
        return items.at(i);
      }
    }
    return nullptr;
  };
  std::shared_ptr<Item> item = DatabaseSimulator::getInstance().findItem(
      createItemByType<BlobItem>()->getTableName(), searchCallback);
  return std::dynamic_pointer_cast<BlobItem>(item);
}

void DatabaseManager::removeBlobItem(const std::string &blobHash) {
  std::function<size_t(std::vector<std::shared_ptr<Item>> &)> searchCallback =
      [&blobHash](std::vector<std::shared_ptr<Item>> &items) -> size_t {
    for (size_t i = 0; i < items.size(); ++i) {
      if (std::dynamic_pointer_cast<BlobItem>(items.at(i))->getBlobHash() ==
          blobHash) {
        return i;
      }
    }
    return size_t(-1);
  };

  DatabaseSimulator::getInstance().removeItem(
      createItemByType<BlobItem>()->getTableName(), searchCallback);
}

void DatabaseManager::putReverseIndexItem(const ReverseIndexItem &item) {
  DatabaseSimulator::getInstance().putItem(
      item.getTableName(),
      std::move(std::make_shared<ReverseIndexItem>(
          item.getHolder(), item.getBlobHash())));
}

std::shared_ptr<ReverseIndexItem>
DatabaseManager::findReverseIndexItemByHolder(const std::string &holder) {
  std::function<std::shared_ptr<Item>(std::vector<std::shared_ptr<Item>> &)>
      searchCallback = [&holder](std::vector<std::shared_ptr<Item>> &items)
      -> std::shared_ptr<Item> {
    for (size_t i = 0; i < items.size(); ++i) {
      if (std::dynamic_pointer_cast<ReverseIndexItem>(items.at(i))
              ->getHolder() == holder) {
        return items.at(i);
      }
    }
    return nullptr;
  };
  std::shared_ptr<Item> item = DatabaseSimulator::getInstance().findItem(
      createItemByType<ReverseIndexItem>()->getTableName(), searchCallback);
  return std::dynamic_pointer_cast<ReverseIndexItem>(item);
}

std::vector<std::shared_ptr<ReverseIndexItem>>
DatabaseManager::findReverseIndexItemsByHash(const std::string &blobHash) {
  std::function<std::vector<std::shared_ptr<Item>>(
      std::vector<std::shared_ptr<Item>> &)>
      searchCallback = [&blobHash](std::vector<std::shared_ptr<Item>> &items)
      -> std::vector<std::shared_ptr<Item>> {
    std::vector<std::shared_ptr<Item>> result;
    for (size_t i = 0; i < items.size(); ++i) {
      if (std::dynamic_pointer_cast<ReverseIndexItem>(items.at(i))
              ->getBlobHash() == blobHash) {
        result.push_back(items.at(i));
      }
    }
    return result;
  };
  std::vector<std::shared_ptr<Item>> items =
      DatabaseSimulator::getInstance().findItems(
          createItemByType<ReverseIndexItem>()->getTableName(), searchCallback);
  std::vector<std::shared_ptr<ReverseIndexItem>> reverseIndexItems;
  for (auto it = items.begin(); it != items.end(); ++it) {
    reverseIndexItems.push_back(
        std::dynamic_pointer_cast<ReverseIndexItem>(std::move(*it)));
  }
  return reverseIndexItems;
}

bool DatabaseManager::removeReverseIndexItem(const std::string &holder) {
  std::function<size_t(std::vector<std::shared_ptr<Item>> &)> searchCallback =
      [&holder](std::vector<std::shared_ptr<Item>> &items) -> size_t {
    for (size_t i = 0; i < items.size(); ++i) {
      if (std::dynamic_pointer_cast<ReverseIndexItem>(items.at(i))
              ->getHolder() == holder) {
        return i;
      }
    }
    return size_t(-1);
  };

  return DatabaseSimulator::getInstance().removeItem(
      createItemByType<ReverseIndexItem>()->getTableName(), searchCallback);
}

} // namespace database
} // namespace network
} // namespace comm
