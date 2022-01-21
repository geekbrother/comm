#include "ConfigManager.h"
#include "Constants.h"

#include <iostream>
#include <sstream>

// Environment variables
const char *TUNNELBROKER_ID_ENV_VAR = "TUNNELBROKER_ID";
const char *DEVICE_SESSIONS_TABLE_NAME_ENV_VAR = "DEVICE_SESSIONS_TABLE_NAME";
const char *SERVER_LISTEN_ADDRESS_ENV_VAR = "SERVER_LISTEN_ADDRESS";
const char *AMQP_URI_ENV_VAR = "AMQP_URI";
const char *AMQP_MESSAGE_TTL_ENV_VAR = "AMQP_MESSAGE_TTL";

int TunnelBrokerConfig::loadConfig() {
  const char *tunnelbrokerIDStr{getenv(TUNNELBROKER_ID_ENV_VAR)};
  const char *deviceSessionsTableNameStr{
      getenv(DEVICE_SESSIONS_TABLE_NAME_ENV_VAR)};
  const char *serverListenAddressStr{getenv(SERVER_LISTEN_ADDRESS_ENV_VAR)};
  const char *amqpURIStr{getenv(AMQP_URI_ENV_VAR)};
  const char *amqpMessageTTLStr{getenv(AMQP_MESSAGE_TTL_ENV_VAR)};

  if (tunnelbrokerIDStr == NULL || deviceSessionsTableNameStr == NULL ||
      serverListenAddressStr == NULL || amqpURIStr == NULL ||
      amqpMessageTTLStr == NULL) {
    return 1;
  }

  tunnelbrokerID = tunnelbrokerIDStr;
  deviceSessionsTableName = deviceSessionsTableNameStr;
  serverListenAddress = serverListenAddressStr;
  amqpURI = amqpURIStr;
  // Try to convert C-style string to size_t
  if (sscanf(amqpMessageTTLStr, "%zu", &amqpMessageTTL) != 1) {
    return 1;
  }

  return 0;
}
