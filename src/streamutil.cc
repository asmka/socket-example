#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <sys/socket.h>

void ListenSocket(const int sockfd, const int backlog) {
  if (listen(sockfd, backlog) == -1) {
    auto msg = std::string("Failed to listen socket: ") + std::strerror(errno);
    throw std::runtime_error(msg);
  }
}
