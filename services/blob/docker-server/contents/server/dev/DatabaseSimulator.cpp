#include "DatabaseSimulator.h"

namespace comm {
namespace network {
namespace database {

DatabaseSimulator DatabaseSimulator::getInstance() {
  static DatabaseSimulator instance;
  return instance;
}

std::mutex DatabaseSimulator::mutex;
std::unordered_map<std::string, std::vector<std::shared_ptr<Item>>>
    DatabaseSimulator::db = {};

void DatabaseSimulator::putItem(
    const std::string &tableName,
    std::shared_ptr<Item> item) {
  const std::lock_guard<std::mutex> lock(mutex);
  auto table = db.find(tableName);
  if (table == db.end()) {
    db.insert({tableName, {}});
  }
  db.at(tableName).push_back(item);
}

std::shared_ptr<Item> DatabaseSimulator::findItem(
    const std::string &tableName,
    const std::function<std::shared_ptr<Item>(std::vector<std::shared_ptr<Item > >&)>
        &searchCallback) const {
  const std::lock_guard<std::mutex> lock(mutex);
  if (db.find(tableName) == db.end()) {
    return nullptr;
  }
  return searchCallback(db.at(tableName));
}

std::vector<std::shared_ptr<Item>> DatabaseSimulator::findItems(
    const std::string &tableName,
    const std::function<std::vector<std::shared_ptr<Item>>(
        std::vector<std::shared_ptr<Item>> &)> &searchCallback) const {
  const std::lock_guard<std::mutex> lock(mutex);
  if (db.find(tableName) == db.end()) {
    return {};
  }
  return searchCallback(db.at(tableName));
}

bool DatabaseSimulator::removeItem(
    const std::string &tableName,
    const std::function<size_t(std::vector<std::shared_ptr<Item>>&)> &searchCallback) {
  const std::lock_guard<std::mutex> lock(mutex);
  auto table = db.find(tableName);
  if (table == db.end()) {
    return false;
  }
  const size_t index = searchCallback(table->second);
  if (index > table->second.size()) {
    return false;
  }
  table->second.erase(db.at(tableName).begin() + index);
  return true;
}

} // namespace database
} // namespace network
} // namespace comm
