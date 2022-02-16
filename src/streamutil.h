#include <string>

void ListenSocket(int rcpt_sfd, int backlog);
int AcceptSocket(int rcpt_sfd);
void ConnectSocket(int sockfd, const std::string &peersockpath);
