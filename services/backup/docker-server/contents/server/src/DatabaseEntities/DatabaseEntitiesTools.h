#pragma once

#include "Item.h"

#include "BlobItem.h"
#include "ReverseIndexItem.h"

#include <memory>

namespace comm {
namespace network {
namespace database {

/**
 * Database - Structure:
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
 *  compactionChildren    list<string>
 *  logs                  list<string>
 * log
 *  id                    string
 *  persistedInBlob       bool
 *  value                 binary
 *  children              list<string>
 */

/**
 * Database - Description:
 *  userPersist - information which user ids are assigned to which backups
 *  backup - tells which backups points to which compactions, also stores backup
 *           keys encrypted with users' passwords.
 *           Has the `created` field so the users can easily fetch backups, see
 *           when they were created and pick a desired one by a creation date.
 *           `compactionID` points to the "parent" compaction.
 *  compaction - this is meant to be stored in blob, therefore it has the
 *               `holder` field to be able to ask blob service for a target blob
 *               `compactionChildren` - this is a list of compaction records
 *                  that come from this one
 *               `logs` - list of log records that belong to this compaction
 *  log - a single log record
 *        `persistedInBlob` - we store this either in this table in the `value`
 *            field or in the blob service
 *        `value` - either the value itself or the holder(if `persistedInBlob`
 *            is true)
 *        `children` - log records that are children of this one
 */

/**
 * Database - Additional notes:
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

/**
 * API - description
 *  CreateNewBackup - This method is called when we want to create a new backup.
 *    We send a new backup key encrypted with the user's password and also the
 *    new compaction. New logs that will be sent from now on will be assigned to
 *    this the compaction of this backup.
 *  SendLog - User sends a new log to the backup service. The log is being
 *    assigned to the latest(or desired) backup's compaction item.
 *  PullBackupKey - Pulls the backup key for the latest(or desired) backup
 *  PullCompaction - Fetches compaction + all logs assigned to it for the
 *    specified backup(default is the last backup)
 */

/**
 * API
 *  CreateNewBackup
 *   receives
 *    - user id
 *    - new encrypted backup key
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
 *    - backup id(optional, default is the latest backup)
 *    - data
 *   performs
 *    - takes the last(or given) `backupID` from the `userPersist` table
 *    - obtain a taget compaction parent from `backup` table
 *    - decides on whether to store the log in the blob or in the DB directly
 *    - adds a record to `log` table
 *    - adds the newly added log id to compaction's `logs`
 *   returns
 *    - nothing(still a status automatically though)
 *  PullBackupKey
 *   receives
 *    - user id
 *    - backup id(optional, default is the latest backup)
 *    - pake key
 *   performs
 *    - verifies user's password with pake
 *    - takes the last(or given) `backupID` from the `userPersist` table
 *    - gets encrypted backup key from the `backup` table
 *   returns
 *    - encrypted backup key
 *  PullCompaction
 *   receives
 *    - user id
 *    - backup id(optional, default is the latest backup)
 *    - pake key
 *   performs
 *    - verifies user's password with pake
 *    - takes the last(or given) `backupID` from the `userPersist` table
 *    - gets `compactionID` from the `backup` table
 *    - obtains compaction(s) and log(s) for this backup
 *   returns
 *    - data in chunks
 */

/**
 * API - Additional notes:
 *  - we may want to create an some more methods that we've not yet discussed if
 *    we want to give the users a possibility to list/pick different versions of
 *    backup.
 *
 */

} // namespace database
} // namespace network
} // namespace comm
