#pragma once

#include <string>

namespace comm {
namespace network {

bool RsaVerifyString(
    const std::string &aPublicKeyStrHex,
    const std::string &aMessage,
    const std::string &aSignatureStrHex);

} // namespace network
} // namespace comm
