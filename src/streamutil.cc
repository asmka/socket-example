#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <sys/un.h>

void ListenSocket(const int rcpt_sfd, const int backlog) {
  if (listen(rcpt_sfd, backlog) == -1) {
    auto msg = std::string("Failed to listen socket: ") + std::strerror(errno);
    throw std::runtime_error(msg);
  }
}

int AcceptSocket(const int rcpt_sfd) {
  int conn_sfd{};
  struct sockaddr peeraddr {};
  socklen_t peeraddrlen{};

  if ((conn_sfd = accept(rcpt_sfd, &peeraddr, &peeraddrlen)) == -1) {
    auto msg = std::string("Failed to accept socket: ") + std::strerror(errno);
    throw std::runtime_error(msg);
  }

  return conn_sfd;
}

void ConnectSocket(const int sockfd, const std::string &peersockpath) {
  struct sockaddr_un addr {};
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, peersockpath.c_str(), sizeof(addr.sun_path) - 1);

  struct sockaddr peeraddr {};
  socklen_t peeraddrlen{};
  if (connect(sockfd, reinterpret_cast<const struct sockaddr *>(&addr),
              sizeof(addr)) == -1) {
    auto msg = std::string("Failed to connect socket: ") + strerror(errno);
    throw std::runtime_error(msg);
  }
}
