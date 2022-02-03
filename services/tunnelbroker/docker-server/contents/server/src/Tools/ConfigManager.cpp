#include "ConfigManager.h"
#include "Constants.h"

#include <fstream>
#include <iostream>

namespace comm {
namespace network {
namespace config {

ConfigManager &ConfigManager::getInstance() {
  static ConfigManager instance;
  return instance;
}

void ConfigManager::load() {
  try {
    std::ifstream fileStream;
    fileStream.open(CONFIG_FILE_PATH.c_str(), std::ifstream::in);
    if (!fileStream.is_open()) {
      throw std::runtime_error("Error: can not open file " + CONFIG_FILE_PATH);
    }

    boost::program_options::options_description description{
        "Tunnelbroker options"};
    description.add_options()(
        "tunnelbroker.instance-id",
        boost::program_options::value<std::string>(),
        "Tunnelbroker unique identification")(
        "keyserver.default_keyserver_id",
        boost::program_options::value<std::string>(),
        "Default and only allowed keyserver deviceID")(
        "amqp.uri",
        boost::program_options::value<std::string>(),
        "AMQP URI connection string")(
        "amqp.fanout_exchange_name",
        boost::program_options::value<std::string>()->default_value(
            AMQP_FANOUT_EXCHANGE_NAME),
        "AMQP Fanout exchange name")(
        "dynamodb.sessions_table_name",
        boost::program_options::value<std::string>()->default_value(
            DEVICE_SESSIONS_TABLE_NAME),
        "DynamoDB table name for sessions")(
        "dynamodb.sessions_verification_table_name",
        boost::program_options::value<std::string>()->default_value(
            DEVICE_SESSIONS_VERIFICATION_MESSAGES_TABLE_NAME),
        "DynamoDB table name for sessions verification messages")(
        "dynamodb.sessions_public_key_table_name",
        boost::program_options::value<std::string>()->default_value(
            DEVICE_PUBLIC_KEY_TABLE_NAME),
        "DynamoDB table name for public keys");

    boost::program_options::parsed_options parsedDescription =
        boost::program_options::parse_config_file(
            fileStream, description, true);
    boost::program_options::store(parsedDescription, this->variablesMap);
    boost::program_options::notify(this->variablesMap);
    fileStream.close();
  } catch (const std::exception &e) {
    throw std::runtime_error(
        "Got an exception at ConfigManager: " + std::string(e.what()));
  }
}

std::string ConfigManager::getParameter(std::string param) {
  if (!this->variablesMap.count(param) &&
      !this->variablesMap[param].defaulted()) {
    throw std::runtime_error(
        "ConfigManager Error: config parameter " + param + " is not set.");
  }
  return this->variablesMap[param].as<std::string>();
}

} // namespace config
} // namespace network
} // namespace comm
