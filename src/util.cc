#include <errno.h>
#include <exception>
#include <netinet/in.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

using namespace std;

int createBindedUnixStreamSocket(const char *path) throw(exception) {
  int sfd;
  sfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sfd != 0) {
    string msg = string("Failed to create socket: ") + strerror(errno);
    throw runtime_error(msg);
  }

  // Bind
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof(sockaddr_un));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, path, sizeof(addr.sun_path) - 1);
  if (bind(sfd, (const struct sockaddr *)&addr, sizeof(addr)) != 0) {
    string msg = string("Failed to bind socket: ") + strerror(errno);
    throw runtime_error(msg);
  }

  return sfd;
}

int main() {
  int sfd = createBindedUnixStreamSocket("./tmp/local_socket");

  // Listen
  listen(sfd, 50);
  printf("Listened.\n");

  // Accept with blocking
  int con_sfd;
  con_sfd = accept(sfd, &peer_addr, &perr_addr_size);
  printf("Accepted.\n");

  const int BUF_SIZE = 1024;
  char *buf = (char *)calloc(BUF_SIZE, sizeof(char));
  while (true) {
    // Read with blocking
    int read_size = read(con_sfd, buf, BUF_SIZE);
    if (read_size > 0) {
      printf("Read: %.*s\n", read_size, buf);
    } else {
      printf("Read End.\n");
      return 0;
    }
  }

  return 0;
}
