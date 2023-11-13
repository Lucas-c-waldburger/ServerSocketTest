#include "LoopAccept.h"
using namespace Utils;

const char IP[] = "localhost";
const char PORT[] = "3490";
const int BACKLOG = 10;

int main()
{
    addrinfo* servInfo, * p;
    addrinfo hints = makeHints();

    if (int retVal = getaddrinfo(nullptr, PORT, &hints, &servInfo) == -1)
    {
        std::cout << "getaddrinfo: " << gai_strerror(retVal);
        return 1;
    }

    int sockFd = bindFirstAvail(servInfo, p);

    freeaddrinfo(servInfo);

    if (!p)
    {
        std::cout << "Server failed to bind";
        return 1;
    }

    if (listen(sockFd, BACKLOG) == -1)
    {
        perror("listen");
        return 1;
    }

    if (!reapDeadProcesses())
        return 1;

    std::cout << "server: waiting for connections...\n";

    MainLoop::waitAccept(sockFd);

    return 0;
}
