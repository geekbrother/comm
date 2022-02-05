#pragma once

#include "Item.h"

#include <string>

namespace comm {
namespace network {
namespace database {

class MessageItem : public Item {
  std::string messageID;
  std::string fromDeviceID;
  std::string toDeviceID;
  std::string payload;
  std::string blobHashes;

  void validate() const override;

public:
  static const std::string FIELD_MESSAGE_ID;
  static const std::string FIELD_FROM_DEVICE_ID;
  static const std::string FIELD_TO_DEVICE_ID;
  static const std::string FIELD_PAYLOAD;
  static const std::string FIELD_BLOB_HASHES;

  std::string getPrimaryKey() const override;
  std::string getTableName() const override;
  std::string getMessageID() const;
  std::string getFromDeviceID() const;
  std::string getToDeviceID() const;
  std::string getPayload() const;
  std::string getBlobHashes() const;

  MessageItem() {
  }
  MessageItem(
      const std::string messageID,
      const std::string fromDeviceID,
      const std::string toDeviceID,
      const std::string payload,
      const std::string blobHashes);
  MessageItem(const AttributeValues &itemFromDB);
  void assignItemFromDatabase(const AttributeValues &itemFromDB) override;
};

} // namespace database
} // namespace network
} // namespace comm
