#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H
#include "includes.h"

namespace Utils
{
    void* castInAddrIPv(sockaddr* sa);

    void sigchldHandler(int s);

    addrinfo makeHints();

    int bindFirstAvail(addrinfo* servInfo, addrinfo* p);

    int setReuse(int sockFd);

    bool reapDeadProcesses();








};


#endif //SOCKET_UTILS_H
