#pragma once

#include "DatabaseEntitiesTools.h"

#include <string>
#include <unordered_map>
#include <mutex>
#include <vector>

namespace comm {
namespace network {
namespace database {

// thread-safe in-memory database
class DatabaseSimulator
{
  DatabaseSimulator() {}
  static std::mutex mutex;
  // map of [table name] => [records]
  static std::unordered_map<std::string, std::vector<std::shared_ptr<Item>>> db;

public:
  static DatabaseSimulator getInstance();

  void putItem(const std::string &tableName, std::shared_ptr<Item> item);

  std::shared_ptr<Item> findItem(
      const std::string &tableName,
      const std::function<std::shared_ptr<Item>(
          std::vector<std::shared_ptr<Item>> &)> &searchCallback) const;

  std::vector<std::shared_ptr<Item>> findItems(
      const std::string &tableName,
      const std::function<std::vector<std::shared_ptr<Item>>(
          std::vector<std::shared_ptr<Item>> &)> &searchCallback) const;

  bool removeItem(
      const std::string &tableName,
      const std::function<size_t(std::vector<std::shared_ptr<Item>> &)> &searchCallback);
};


} // namespace database
} // namespace network
} // namespace comm
