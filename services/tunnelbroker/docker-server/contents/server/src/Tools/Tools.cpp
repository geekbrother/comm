#include "Tools.h"
#include "Constants.h"

#include <algorithm>
#include <chrono>

namespace comm {
namespace network {

std::string generateRandomString(std::size_t length) {
  const std::string CHARACTERS =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  std::random_device random_device;
  std::mt19937 generator(random_device());
  std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);
  std::string random_string;
  for (std::size_t i = 0; i < length; ++i) {
    random_string += CHARACTERS[distribution(generator)];
  }
  return random_string;
}

long long getCurrentTimestamp() {
  using namespace std::chrono;
  return duration_cast<milliseconds>(system_clock::now().time_since_epoch())
      .count();
}

bool validateDeviceId(std::string deviceId) {
  // We are allow only one keyserver for now
  if (deviceId == DEVICEID_DEFAULT_KEYSERVER_ID) {
    return true;
  }
  const std::string delimiter = ":";
  const std::string prefix = deviceId.substr(0, deviceId.find(delimiter));
  const std::string suffix = deviceId.substr(
      deviceId.find(delimiter), deviceId.length() - deviceId.find(delimiter));
  // Reject all key servers except one allowed before
  if (prefix == "ks") {
    return false;
  }
  std::vector<std::string> deviceTypes{"ks", "mobile", "web"};
  if (std::find(std::begin(deviceTypes), std::end(deviceTypes), prefix) ==
      std::end(deviceTypes)) {
    return false;
  }
  if ((suffix.length() - 1) != DEVICEID_CHAR_LENGTH) {
    return false;
  }
  return true;
}

} // namespace network
} // namespace comm
