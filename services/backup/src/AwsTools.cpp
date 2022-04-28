#include "AwsTools.h"
#include "Constants.h"

#include <cstdlib>

namespace comm {
namespace network {

std::unique_ptr<Aws::DynamoDB::DynamoDBClient> getDynamoDBClient() {
  Aws::Client::ClientConfiguration config;
  config.region = AWS_REGION;
  if (std::string(
          std::getenv("COMM_SERVICES_DEV_MODE")
              ? std::getenv("COMM_SERVICES_DEV_MODE")
              : "") == "1") {
    config.endpointOverride = Aws::String("localstack:4566");
    config.scheme = Aws::Http::Scheme::HTTP;
  }
  return std::make_unique<Aws::DynamoDB::DynamoDBClient>(config);
}

} // namespace network
} // namespace comm
