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
      throw std::runtime_error(
          "ConfigManager Error: can not open file " + CONFIG_FILE_PATH);
    }

    boost::program_options::options_description desc{"Tunnelbroker options"};
    desc.add_options()(
        "tunnelbroker.instance-id",
        boost::program_options::value<std::string>(),
        "Tunnelbroker unique identification")(
        "amqp.uri",
        boost::program_options::value<std::string>(),
        "AMQP URI connection string");

    boost::program_options::parsed_options parsedc =
        boost::program_options::parse_config_file(fileStream, desc, true);
    boost::program_options::store(parsedc, this->variablesMap);
    boost::program_options::notify(this->variablesMap);
    fileStream.close();
  } catch (const std::exception &e) {
    throw std::runtime_error(
        "Got an exception at ConfigManager: " + std::string(e.what()));
  }
}

std::string ConfigManager::getParameter(std::string param) {
  if (!this->variablesMap.count(param)) {
    throw std::runtime_error(
        "ConfigManager Error: config parameter " + param + " is not set.");
  }
  return this->variablesMap[param].as<std::string>();
}

} // namespace config
} // namespace network
} // namespace comm
