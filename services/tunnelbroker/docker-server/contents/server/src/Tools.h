#pragma once

#include "Constants.h"
#include "Tools.cpp"
#include <folly/MPMCQueue.h>
#include <string>

namespace comm {
namespace network {
namespace ping {

struct ClientData {
  const std::string id;
  const std::string deviceToken;

  folly::MPMCQueue<bool> pingRequests = folly::MPMCQueue<bool>(10);
  folly::MPMCQueue<bool> pingResponses = folly::MPMCQueue<bool>(10);
  ClientState lastState = ClientState::ONLINE;

  ClientData(const std::string id, const std::string deviceToken)
      : id(id), deviceToken(deviceToken) {
  }
};

enum class ClientState {
  ONLINE,
  OFFLINE,
};

enum class ResponseStatus {
  SUCCESS,
  ERROR,
};

} // namespace ping
} // namespace network
} // namespace comm
