#pragma once

#include "AwsTools.h"
#include "DatabaseEntitiesTools.h"

#include <aws/core/Aws.h>
#include <aws/dynamodb/model/AttributeDefinition.h>
#include <aws/dynamodb/model/DeleteItemRequest.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/PutItemRequest.h>

#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace comm {
namespace network {
namespace database {

class DatabaseManager {

  void innerPutItem(
      std::shared_ptr<Item> item,
      const Aws::DynamoDB::Model::PutItemRequest &request);

  template <typename T>
  std::shared_ptr<T>
  innerFindItem(Aws::DynamoDB::Model::GetItemRequest &request);
  // the key is either
  //  - fileHash for blob items
  //  - reverseIndex for reverse index items
  template <typename T> void innerRemoveItem(const std::string &key);

public:
  static DatabaseManager &getInstance();

  void putBlobItem(const BlobItem &item);
  std::shared_ptr<BlobItem> findBlobItem(const std::string &fileHash);
  void removeBlobItem(const std::string &fileHash);

  void putReverseIndexItem(const ReverseIndexItem &item);
  std::shared_ptr<ReverseIndexItem>
  findReverseIndexItemByReverseIndex(const std::string &reverseIndex);
  std::vector<std::shared_ptr<database::ReverseIndexItem>>
  findReverseIndexItemsByHash(const std::string &fileHash);
  void removeReverseIndexItem(const std::string &reverseIndex);

  std::vector<std::string> getAllHashes();
};

template <typename T>
std::shared_ptr<T>
DatabaseManager::innerFindItem(Aws::DynamoDB::Model::GetItemRequest &request) {
  std::shared_ptr<T> item = createItemByType<T>();
  // Set up the request
  request.SetTableName(item->getTableName());
  // Retrieve the item's fields and values
  const Aws::DynamoDB::Model::GetItemOutcome &outcome =
      AwsObjectsFactory::getDynamoDBClient()->GetItem(request);
  if (!outcome.IsSuccess()) {
    throw std::runtime_error(outcome.GetError().GetMessage());
  }
  const AttributeValues &outcomeItem = outcome.GetResult().GetItem();
  if (!outcomeItem.size()) {
    // todo print a fileHash here
    std::cout << "no item found" << std::endl;
    return nullptr;
  }
  item->assignItemFromDatabase(outcomeItem);
  return std::move(item);
}

template <typename T>
void DatabaseManager::innerRemoveItem(const std::string &key) {
  Aws::DynamoDB::Model::DeleteItemRequest request;
  // I couldn't avoid DRY here as those requests inherit from DynamoDBRequest
  // and that class does not have a method `SetTableName`
  std::shared_ptr<T> item = createItemByType<T>();
  request.SetTableName(item->getTableName());
  request.AddKey(
      item->getPrimaryKey(), Aws::DynamoDB::Model::AttributeValue(key));

  const Aws::DynamoDB::Model::DeleteItemOutcome &outcome =
      AwsObjectsFactory::getDynamoDBClient()->DeleteItem(request);
  if (!outcome.IsSuccess()) {
    throw std::runtime_error(outcome.GetError().GetMessage());
  }
}

} // namespace database
} // namespace network
} // namespace comm
