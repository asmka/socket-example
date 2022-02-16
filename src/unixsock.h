#include <string>

int CreateUnixStreamSocket();
void BindUnixSocket(const int sockfd, const std::string sockpath);
