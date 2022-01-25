#include "ConfigManager.h"
#include "Constants.h"

#include <sstream>

// Environment variables
const char *TUNNELBROKER_ID_ENV_VAR = "COMM_TUNNELBROKER_ID";
const char *DEVICE_SESSIONS_TABLE_NAME_ENV_VAR =
    "COMM_TUNNELBROKER_DEVICE_SESSIONS_TABLE_NAME";
const char *SERVER_LISTEN_ADDRESS_ENV_VAR =
    "COMM_TUNNELBROKER_SERVER_LISTEN_ADDRESS";
const char *AMQP_URI_ENV_VAR = "COMM_TUNNELBROKER_AMQP_URI";
const char *AMQP_MESSAGE_TTL_ENV_VAR = "COMM_TUNNELBROKER_AMQP_MESSAGE_TTL";

void TunnelbrokerConfig::loadConfig() {
  this->tunnelbrokerID = getenv(TUNNELBROKER_ID_ENV_VAR);
  this->deviceSessionsTableName = getenv(DEVICE_SESSIONS_TABLE_NAME_ENV_VAR);
  this->serverListenAddress = getenv(SERVER_LISTEN_ADDRESS_ENV_VAR);
  this->amqpURI = getenv(AMQP_URI_ENV_VAR);
  const char *amqpMessageTTLStr{getenv(AMQP_MESSAGE_TTL_ENV_VAR)};

  if (tunnelbrokerID == NULL || deviceSessionsTableName == NULL ||
      serverListenAddress == NULL || amqpURI == NULL ||
      amqpMessageTTLStr == NULL) {
    throw std::runtime_error("config environment variable(s) not set");
  }

  // Try to convert C-style string to size_t
  if (sscanf(amqpMessageTTLStr, "%zu", &this->amqpMessageTTL) != 1) {
    throw std::runtime_error("could not read size_t from amqpMessageTTLStr");
  }
}
