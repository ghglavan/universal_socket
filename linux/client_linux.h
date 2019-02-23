#pragma once

#include "common_linux.h"

namespace sock
{
int connect(UniversalSocket &connect_socket, std::string server_name, uint16_t port)
{
    struct hostent *he;
    struct sockaddr_in their_addr;

    if ((he = gethostbyname(server_name.c_str())) == NULL)
    {
        herror("error in gethostbyname:");
        return -1;
    }

    if ((connect_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("error in socket:");
        return -2;
    }

    their_addr.sin_family = AF_INET;
    their_addr.sin_port = htons(port);
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero), 8);

    if (connect(connect_socket, (struct sockaddr *)&their_addr,
                sizeof(struct sockaddr)) == -1)
    {
        perror("error in connect:");
        return -3;
    }

    return 0;
}

}; // namespace sock
