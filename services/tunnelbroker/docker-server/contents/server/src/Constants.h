#pragma once

#include <string>

// AWS
const std::string AWS_REGION = "us-east-2";
const std::string DEVICE_SESSIONS_TABLE_NAME = "tunnelbroker-service-devices";

// gRPC
// 4MB limit
const size_t GRPC_CHUNK_SIZE_LIMIT = 4 * 1024 * 1024;
const size_t GRPC_METADATA_SIZE_PER_MESSAGE = 5;

// Sessions
const size_t SESSION_ID_LENGTH = 16;
