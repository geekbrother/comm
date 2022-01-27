#pragma once

#include "Item.h"

#include "BlobItem.h"
#include "ReverseIndexItem.h"

#include <memory>

namespace comm {
namespace network {
namespace database {

/**
 * Database Structure:
 * userPersist
 *  userID                string
 *  backupIDs             list<string>
 * backup
 *  id                    string
 *  compactionID          string
 *  encryptedBackupKey    string
 *  created               timestamp
 * compaction
 *  id                    string
 *  holder                string
 *  children              list<string>
 * log
 *  id                    string
 *  compactionID          string
 *  persistedInBlob       bool
 *  value                 binary
 *  children              list<string>
 */

template <typename T> std::shared_ptr<T> createItemByType() {
  throw std::runtime_error("invalid Item type");
}

// template <> std::shared_ptr<?> createItemByType<?>();

/**
 * API
 *  ResetKey
 *   receives
 *    - user id
 *    - new encrypted backup key
 *    - new compaction holder
 *    - new compaction in chunks
 *   performs
 *    - adds a new record(s) to `compaction` table
 *    - adds a record to `backup` table
 *    - adds a backup to `userPersist` table
 *   returns
 *    - nothing(still a status automatically though)
 *  SendLog
 *   receives
 *    - user id
 *    - data
 *   performs
 *    - takes the last `backupID` from the `userPersist` table
 *    - gets the `compactionID` from `backup` table
 *    - decides on whether to store the log in the blob or in the DB directly
 *    - adds a record to `log` table
 *   returns
 *    - nothing(still a status automatically though)
 *  PullBackupKey
 *   receives
 *    - user id
 *    - pake key
 *   performs
 *    - verifies user's password with pake
 *    - takes the last `backupID` from the `userPersist` table
 *    - gets encrypted backup key from the `backup` table
 *   returns
 *    - encrypted backup key
 *  PullCompaction
 *   receives
 *    - user id
 *   performs
 *    - takes the last `backupID` from the `userPersist` table
 *    - gets `compactionID` from the `backup` table
 *    - obtains compaction(s) and log(s) for this backup
 *   returns
 *    - data in chunks
 */

/**
 * Additional notes:
 *  - with `userPersist` table we can easily get a list of backups and give
 *    users a possibility to pull older backups in the future
 *  - the reason we have two distinct tables `userPersist` and `backup` is that
 *    each backup has a separate encrypted backup key. So I think this way is
 *    more clean than having something like this:
 *      userPersist
 *        userID                string
 *        backups               list<tuple<string, string>>
 *          where the tuple consists of
 *            - compaction id
 *            - encrypted backup key
 *  - each backup key can be decrypted with the user's password, right?
 *
 */

} // namespace database
} // namespace network
} // namespace comm
