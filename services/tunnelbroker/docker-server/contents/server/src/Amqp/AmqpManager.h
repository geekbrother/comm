#pragma once

#include "Constants.h"
#include "DeliveryBroker.h"

#include <boost/asio/deadline_timer.hpp>
#include <boost/asio/io_service.hpp>
#include <boost/asio/strand.hpp>

#include <amqpcpp.h>
#include <amqpcpp/libboostasio.h>
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
