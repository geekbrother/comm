#pragma once

#include <random>
#include <string>

namespace comm {
namespace network {

std::string generateRandomString(std::size_t length);
long long getCurrentTimestamp();
bool validateDeviceId(std::string deviceId);
std::string generateUUID();
bool validateSessionId(std::string sessionId);

} // namespace network
} // namespace comm
