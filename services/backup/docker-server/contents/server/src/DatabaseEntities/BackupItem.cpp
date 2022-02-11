#include "BackupItem.h"

#include "Constants.h"

namespace comm {
namespace network {
namespace database {

const std::string BackupItem::FIELD_USER_ID = "userID";
const std::string BackupItem::FIELD_CREATED = "created";
const std::string BackupItem::FIELD_BACKUP_ID = "backupID";
const std::string BackupItem::FIELD_RECOVERY_DATA = "recoveryData";
const std::string BackupItem::FIELD_COMPACTION_HOLDER = "compactionHolder";
const std::string BackupItem::FIELD_ATTACHMENT_HOLDERS = "attachmentHolders";

std::string BackupItem::tableName = BACKUP_TABLE_NAME;

BackupItem::BackupItem(
    std::string userID,
    uint64_t created,
    std::string backupID,
    std::string recoveryData,
    std::string compactionHolder,
    std::vector<std::string> attachmentHolders)
    : userID(userID),
      created(created),
      backupID(backupID),
      recoveryData(recoveryData),
      compactionHolder(compactionHolder),
      attachmentHolders(attachmentHolders) {
  this->validate();
}

BackupItem::BackupItem(const AttributeValues &itemFromDB) {
  this->assignItemFromDatabase(itemFromDB);
}

void BackupItem::validate() const {
  if (!this->userID.size()) {
    throw std::runtime_error("userID empty");
  }
  if (!this->created) {
    throw std::runtime_error("created not provided");
  }
  if (!this->backupID.size()) {
    throw std::runtime_error("backupID empty");
  }
  if (!this->recoveryData.size()) {
    throw std::runtime_error("recoveryData empty");
  }
  if (!this->compactionHolder.size()) {
    throw std::runtime_error("compactionHolder empty");
  }
}

void BackupItem::assignItemFromDatabase(const AttributeValues &itemFromDB) {
  try {
    this->userID = itemFromDB.at(BackupItem::FIELD_USER_ID).GetS();
    this->created = std::stoll(
        std::string(itemFromDB.at(BackupItem::FIELD_CREATED).GetS()).c_str());
    this->backupID = itemFromDB.at(BackupItem::FIELD_BACKUP_ID).GetS();
    this->recoveryData = itemFromDB.at(BackupItem::FIELD_RECOVERY_DATA).GetS();
    this->compactionHolder =
        itemFromDB.at(BackupItem::FIELD_COMPACTION_HOLDER).GetS();
    this->attachmentHolders =
        itemFromDB.at(BackupItem::FIELD_ATTACHMENT_HOLDERS).GetSS();
  } catch (std::logic_error &e) {
    throw std::runtime_error(
        "invalid backup item provided, " + std::string(e.what()));
  }
  this->validate();
}

std::string BackupItem::getTableName() const {
  return BackupItem::tableName;
}

PrimaryKey BackupItem::getPrimaryKey() const {
  return PrimaryKey(BackupItem::FIELD_USER_ID, BackupItem::FIELD_CREATED);
}

PrimaryKeyValue BackupItem::getPrimaryKeyValue() const {
  return PrimaryKeyValue(this->userID, std::to_string(this->created));
}

std::string BackupItem::getUserID() const {
  return this->userID;
}

uint64_t BackupItem::getCreated() const {
  return this->created;
}

std::string BackupItem::getBackupID() const {
  return this->backupID;
}

std::string BackupItem::getRecoveryData() const {
  return this->recoveryData;
}

std::string BackupItem::getCompactionHolder() const {
  return this->compactionHolder;
}

std::vector<std::string> BackupItem::getAttachmentHolders() const {
  return this->attachmentHolders;
}

} // namespace database
} // namespace network
} // namespace comm
