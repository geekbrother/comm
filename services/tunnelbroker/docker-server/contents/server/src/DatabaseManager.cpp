#include "DatabaseManager.h"
#include "Tools.h"

#include <aws/core/utils/Outcome.h>
#include <aws/dynamodb/model/QueryRequest.h>
#include <aws/dynamodb/model/ScanRequest.h>

#include <iostream>

namespace comm {
namespace network {
namespace database {

DatabaseManager &DatabaseManager::getInstance() {
  static DatabaseManager instance;
  return instance;
}

void DatabaseManager::innerPutItem(
    std::shared_ptr<Item> item,
    const Aws::DynamoDB::Model::PutItemRequest &request) {
  const Aws::DynamoDB::Model::PutItemOutcome outcome =
      AwsObjectsFactory::getDynamoDBClient()->PutItem(request);
  if (!outcome.IsSuccess()) {
    throw std::runtime_error(outcome.GetError().GetMessage());
  }
}

void DatabaseManager::putSessionItem(const DeviceSessionItem &item) {
  Aws::DynamoDB::Model::PutItemRequest request;
  request.SetTableName(DeviceSessionItem::tableName);
  request.AddItem(
      DeviceSessionItem::FIELD_SESSION_ID,
      Aws::DynamoDB::Model::AttributeValue(item.getSessionId()));
  request.AddItem(
      DeviceSessionItem::FIELD_DEVICE_ID,
      Aws::DynamoDB::Model::AttributeValue(item.getLocalDeviceId()));
  request.AddItem(
      DeviceSessionItem::FIELD_USER_ID,
      Aws::DynamoDB::Model::AttributeValue(item.getUserId()));
  request.AddItem(
      DeviceSessionItem::FIELD_NOTIFY_TOKEN,
      Aws::DynamoDB::Model::AttributeValue(item.getNotifyToken()));
  request.AddItem(
      DeviceSessionItem::FIELD_TYPE_OS,
      Aws::DynamoDB::Model::AttributeValue(item.getTypeOS()));
  request.AddItem(
      DeviceSessionItem::FIELD_CHECKPOINT_TIME,
      Aws::DynamoDB::Model::AttributeValue(
          std::to_string(item.getCheckpointTime())));

  this->innerPutItem(std::make_shared<DeviceSessionItem>(item), request);
}

std::shared_ptr<DeviceSessionItem>
DatabaseManager::findSessionItem(const std::string &sessionId) {
  Aws::DynamoDB::Model::GetItemRequest request;
  request.AddKey(
      DeviceSessionItem::FIELD_SESSION_ID,
      Aws::DynamoDB::Model::AttributeValue(sessionId));
  return std::move(this->innerFindItem<DeviceSessionItem>(request));
}

} // namespace database
} // namespace network
} // namespace comm
