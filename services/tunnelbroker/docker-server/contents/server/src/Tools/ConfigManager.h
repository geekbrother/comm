#pragma once

#include <boost/program_options.hpp>

#include <iostream>
#include <string>

namespace comm {
namespace network {
namespace config {

class ConfigManager {
private:
  boost::program_options::variables_map variablesMap;

public:
  static ConfigManager &getInstance();
  void load();
  std::string getParameter(std::string param);
};

} // namespace config
} // namespace network
} // namespace comm
