#pragma once

namespace comm {
namespace network {

struct EndConnectionError : public std::exception {
  const char *what() const throw() {
    return "connection ended";
  }
};

} // namespace network
} // namespace comm
