#pragma once

#include "Item.h"

#include <string>

namespace comm {
namespace network {
namespace database {

class SessionSignItem : public Item {
  std::string sign;
  std::string deviceId;

  void validate() const override;

public:
  static std::string tableName;
  static const std::string FIELD_SESSION_SIGN;
  static const std::string FIELD_DEVICE_ID;
  static const std::string FIELD_TTL;

  std::string getPrimaryKey() const override;
  std::string getTableName() const override;
  std::string getSign() const;
  std::string getDeviceId() const;

  SessionSignItem() {
  }
  SessionSignItem(const std::string sign, const std::string deviceId);
  SessionSignItem(const AttributeValues &itemFromDB);
  void assignItemFromDatabase(const AttributeValues &itemFromDB) override;
};

} // namespace database
} // namespace network
} // namespace comm
