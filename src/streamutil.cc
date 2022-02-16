#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <sys/socket.h>

void ListenSocket(const int rcpt_sfd, const int backlog) {
  if (listen(rcpt_sfd, backlog) == -1) {
    auto msg = std::string("Failed to listen socket: ") + std::strerror(errno);
    throw std::runtime_error(msg);
  }
}

int AcceptSocket(const int rcpt_sfd) {
  int conn_sfd{};
  struct sockaddr peeraddr {};
  socklen_t peeraddr_len{};

  if ((conn_sfd = accept(rcpt_sfd, &peeraddr, &peeraddr_len)) == -1) {
    auto msg = std::string("Failed to accept socket: ") + std::strerror(errno);
    throw std::runtime_error(msg);
  }

  return conn_sfd;
}
