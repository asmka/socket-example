#include "unixsock.h"
#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>

int CreateUnixStreamSocket() {
  // Create socket
  int sockfd;
  sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sockfd == -1) {
    auto msg = std::string("Failed to create socket: ") + strerror(errno);
    throw std::runtime_error(msg);
  }

  return sockfd;
}

void BindUnixSocket(const int sockfd, const std::string &sockpath) {
  // Bind
  struct sockaddr_un addr {};
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, sockpath.c_str(), sizeof(addr.sun_path) - 1);

  if (bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr)) == -1) {
    auto msg = std::string("Failed to bind socket: ") + strerror(errno);
    throw std::runtime_error(msg);
  }
}
