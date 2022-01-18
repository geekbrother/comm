#pragma once

#include <amqpcpp.h>
#include <amqpcpp/libboostasio.h>

#include <atomic>
#include <memory>
#include <string>

namespace comm {
namespace network {

std::unique_ptr<AMQP::TcpChannel> AmqpChannel;
std::atomic<bool> AmqpReady;

void AMQPConnect();
bool AMQPSend(
    std::string toDeviceID,
    std::string fromDeviceID,
    std::string payload);

} // namespace network
} // namespace comm
