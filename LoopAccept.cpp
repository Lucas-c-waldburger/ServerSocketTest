#include "LoopAccept.h"

void MainLoop::waitAccept(int sockFd)
{
    int clientFd;
    sockaddr_storage clientAddr;
    socklen_t sinSize = sizeof(clientAddr);
    char clientAddrStr[INET6_ADDRSTRLEN];

    const char msg[] = "Hello, World!";
    const int CHILD = 0;

    while (1)
    {
        clientFd = accept(sockFd, (sockaddr *)&clientAddr, &sinSize);

        if (clientFd == -1)
        {
            perror("accept");
            continue;
        }

        inet_ntop(clientAddr.ss_family, castInAddrIPv((sockaddr *)&clientAddr), clientAddrStr, sizeof(clientAddrStr));
        std::cout << "server: got connection from " << clientAddrStr << '\n';

        if (fork() == CHILD)
        {
            close(sockFd); // child doesn't need listener fd

            if (send(clientFd, msg, 13, 0) == -1)
                perror("send");

            close(clientFd);
            return;
        }

        // else is parent process or child creation was unsuccessful
        close(clientFd);
    }
}
