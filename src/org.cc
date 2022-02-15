#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int makeUnixStreamSocket() {
  int sfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sfd < 0) {
    throw "socket failed\n";
  }
  return sfd;
}

int main() {
  int sfd = makeUnixStreamSocket();
  struct sockaddr peer_addr;
  socklen_t perr_addr_size;

  // Bind
  struct sockaddr_un local_addr;
  memset(&local_addr, 0, sizeof(sockaddr_un));
  local_addr.sun_family = AF_UNIX;
  strncpy(local_addr.sun_path, "./tmp/local_socket",
          sizeof(local_addr.sun_path) - 1);
  int rtn_bind =
      bind(sfd, (const struct sockaddr *)&local_addr, sizeof(local_addr));
  printf("Binded, rtn: %d\n", rtn_bind);

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
