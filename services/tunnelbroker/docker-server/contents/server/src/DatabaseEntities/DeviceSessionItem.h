#pragma once

#include "Item.h"
#include <string>

namespace comm {
namespace network {
namespace database {

class DeviceSessionItem : public Item {
  std::string sessionId;
  std::string localDeviceId;
  std::string userId;
  std::string notifyToken;
  std::string typeOS;
  long long checkpointTime = 0;

  void validate() const override;

public:
  static std::string tableName;
  // Items attributes name
  static const std::string FIELD_SESSION_ID;
  static const std::string FIELD_DEVICE_ID;
  static const std::string FIELD_USER_ID;
  static const std::string FIELD_NOTIFY_TOKEN;
  static const std::string FIELD_TYPE_OS;
  static const std::string FIELD_CHECKPOINT_TIME;

  DeviceSessionItem();
  DeviceSessionItem(
      const std::string sessionId,
      const std::string localDeviceId,
      const std::string userId,
      const std::string notifyToken,
      const std::string typeOS);
  DeviceSessionItem(const AttributeValues &itemFromDB);
  void assignItemFromDatabase(const AttributeValues &itemFromDB) override;

  // Getters
  std::string getPrimaryKey() const override;
  std::string getTableName() const override;
  std::string getSessionId() const;
  std::string getLocalDeviceId() const;
  std::string getUserId() const;
  std::string getNotifyToken() const;
  std::string getTypeOS() const;
  long long getCheckpointTime() const;
};

} // namespace database
} // namespace network
} // namespace comm
