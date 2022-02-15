#include "unixsocket.h"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int CreateUnixStreamSocket(const std::string sockpath) {
  int sfd;
  sfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sfd == -1) {
    auto msg = std::string("Failed to create socket: ") + strerror(errno);
    throw std::runtime_error(msg);
  }

  // Bind
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, sockpath.c_str(), sizeof(addr.sun_path) - 1);
  if (bind(sfd, (const struct sockaddr *)&addr, sizeof(addr)) != 0) {
    auto msg = std::string("Failed to bind socket: ") + strerror(errno);
    throw std::runtime_error(msg);
  }

  return sfd;
}
