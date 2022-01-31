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
 * backup
 *  userID[PK]            string
 *  backupID[SK]          string
 *  created[SI_1]         timestamp
 *  recoveryData          bytes
 *  compactionHolder      string
 *  attachmentHolders     list<string>
 * log
 *  backupID[PK]          string
 *  logID[SK]             string
 *  persistedInBlob       bool
 *  value                 bytes
 *  attachmentHolders     list<string>
 */

/**
 * Database - Indexes:
 * SI_1
 *  userID[PK]            string
 *  created[SK]           timestamp
 *  backupID              string
 *  recoveryData          bytes
 */

/**
 * Database - Description:
 *  backup - backups assigned to users along with the data necessary to decrypt
 *        `created` - when the backup was created. This is a search key because
 *           we want to be able to perform effective queries based on this info
 *           (for example get me the latest backup, get me backup from some day)
 *        `attachmentHolders` - this is a list of attachment references
 *        `recoveryData` - data serialized with protobuf which is described by
 *           one of the following structures:
 *            { authType: 'password', pakeSecret: string, nonce: string }
 *            { authType: 'wallet', walletAddress: string, rawMessage: string }
 *  log - a single log record
 *        `backupID` - id of the backup that this log is assigned to
 *        `value` - either the value itself(if `persistedInBlob` is false)
 *           or the holder to blob(if `persistedInBlob` is true)
 *        `attachmentHolders` - this is a list of attachment references
 */

/**
 * API - description
 *  CreateNewBackup - This method is called when we want to create a new backup.
 *    We send a new backup key encrypted with the user's password and also the
 *    new compaction. New logs that will be sent from now on will be assigned to
 *    this the compaction of this backup.
 *  SendLog - User sends a new log to the backup service. The log is being
 *    assigned to the latest(or desired) backup's compaction item.
 *  RecoverBackupKey - Pulls data necessary for regenerating the backup key
 *    on the client-side for the latest(or desired) backup
 *  PullBackup - Fetches compaction + all logs assigned to it for the
 *    specified backup(default is the last backup)
 */

/**
 * API - notes
 *  authentication - if it breaks, we do not read/send further data, we cut the
 *    stream and end the connection
 */

/**
 * API
 *  CreateNewBackup(full auth)
 *   receives
 *    - request bytes(auth)
 *    - user id
 *    - authentication data:
 *      - method: password/wallet
 *      - nonce(for password auth)/rawMessage(for wallet auth)
 *    - new compaction in chunks
 *   performs
 *    - authentication(bidi stream)
 *    - adds a record to `backup` table
 *   returns
 *    - response bytes(auth)
 *    - backup id
 *
 *  SendLog(simple auth)
 *   receives
 *    - user id
 *    - backup id
 *    - data
 *   performs
 *    - authentication - checks the backup id
 *    - decides on whether to store the log in the blob or in the DB directly
 *    - adds a record to `log` table
 *   returns
 *    - nothing(still a status automatically though)
 *
 *  RecoverBackupKey(full auth)
 *   receives
 *    - request bytes(auth)
 *    - user id
 *    - backup created date(optional, default is the latest backup)
 *   performs
 *    - authentication(bidi stream)
 *    - searches the `backup` table for a backup of a given creation timestamp(
 *              or by default takes the newest one)
 *   returns
 *    - response bytes(auth)
 *    - nonce(password auth)/raw message(wallet auth)
 *    - backup id
 *
 *  PullBackup(simple auth)
 *   receives
 *    - user id
 *    - backup id
 *   performs
 *    - authentication - checks the backup id
 *    - obtains compaction and log(s) for this backup
 *   returns
 *    - data in chunks
 */

} // namespace database
} // namespace network
} // namespace comm
