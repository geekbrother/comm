#pragma once

#include "Item.h"

#include "LogItem.h"

#include <memory>
#include <type_traits>

namespace comm {
namespace network {
namespace database {

/**
 * Database - Structure:
 * backup
 *  userID[PK]            string
 *  created[SK]           timestamp
 *  backupID              string
 *  recoveryData          bytes
 *  encryptedBackupKey    bytes
 *  compactionHolder      string
 *  attachmentHolders     list<string>
 * log
 *  backupID[PK]          string
 *  logID[SK]             string
 *  persistedInBlob       bool
 *  value                 bytes
 *  attachmentHolders     list<string>
 */

template <typename T> std::shared_ptr<T> createItemByType() {
  static_assert(std::is_base_of<Item, T>::value, "T must inherit from Item");
  return std::make_shared<T>();
}

} // namespace database
} // namespace network
} // namespace comm
