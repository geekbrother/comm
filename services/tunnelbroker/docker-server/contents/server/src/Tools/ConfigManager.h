#pragma once

#include <string>

struct TunnelBrokerConfig {
  // Tunnelbroker server identification
  std::string tunnelbrokerID;

  // AWS
  std::string deviceSessionsTableName;

  // gRPC Server
  std::string serverListenAddress;

  // AMQP (RabbitMQ)
  std::string amqpURI;
  size_t amqpMessageTTL;

  int loadConfig();
};
