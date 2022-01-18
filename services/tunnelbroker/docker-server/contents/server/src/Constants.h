#pragma once

#include <string>

namespace comm {
namespace network {

// Tunnelbroker server Identification
const std::string TUNNELBROKER_ID = "tunnel1";

// AWS
const std::string DEVICE_SESSIONS_TABLE_NAME = "tunnelbroker-service-device";
const std::string DEVICE_SESSIONS_SIGN_TABLE_NAME = "tunnelbroker-session-sign";

// Sessions
const size_t SIGNATURE_REQUEST_LENGTH = 32;
const size_t SESSION_ID_LENGTH = 16;

// gRPC Server
const std::string SERVER_LISTEN_ADDRESS = "0.0.0.0:50051";

// gRPC Settings
const size_t GRPC_CHUNK_SIZE_LIMIT = 4 * 1024 * 1024; // 4 Mb limit
const size_t GRPC_METADATA_SIZE_PER_MESSAGE = 5;

// AMQP (RabbitMQ)
// number of the AMQP client threads
const size_t AMQP_CLIENT_THREADS = 1;
const std::string AMQP_URI = "amqp://commtest:comm2828@195.242.161.52/commapp";
// message TTL
const size_t AMQP_MESSAGE_TTL = 3600 * 1000; // 1 hour
// queue TTL in case of no consumers (tunnelbroker is down)
const size_t AMQP_QUEUE_TTL = 24 * 3600 * 1000; // 24 hours
// routing message headers name
const std::string AMQP_HEADER_FROM_DEVICEID = "from-deviceid";
const std::string AMQP_HEADER_TO_DEVICEID = "to-deviceid";

} // namespace network
} // namespace comm
