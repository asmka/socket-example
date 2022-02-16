#include <string>

int CreateUnixStreamSocket();
void BindUnixSocket(int sockfd, const std::string &sockpath);
