#pragma once

#include <amqpcpp.h>

#include <atomic>
#include <memory>
#include <string>

namespace comm {
namespace network {

void AMQPConnect();
bool AMQPSend(
    std::string toDeviceID,
    std::string fromDeviceID,
    std::string payload);

} // namespace network
} // namespace comm
