#pragma once

#define WIN32_LEAN_AND_MEAN

#include "common_windows.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

namespace sock
{

int connect(UniversalSocket &connect_socket, std::string server_name, uint16_t port)
{
    struct addrinfo *result = NULL,
                    *ptr = NULL,
                    hints;

    int i_result;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    i_result = getaddrinfo(server_name.c_str(), std::to_string(port).c_str(), &hints, &result);
    if (i_result != 0)
    {
        fprintf(stderr, "Error with getaddrinfo (maybe server name is wrong). Error nr: %d", i_result);
        uninit(connect_socket);
        return -1;
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
    {
        int i_result;

        connect_socket = socket(ptr->ai_family, ptr->ai_socktype,
                                ptr->ai_protocol);
        if (connect_socket == INV_SOCK)
        {
            fprintf(stderr, "Error creating socket. Error nr: %d", i_result);
            uninit(connect_socket);
            return -2;
        }

        i_result = ::connect(connect_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (i_result == SOCKET_ERROR)
        {
            closesocket(connect_socket);
            connect_socket = INV_SOCK;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (connect_socket == INV_SOCK)
    {
        fprintf(stderr, "Unable to connect to server");
        uninit(connect_socket);
        return -3;
    }

    return 0;
}
}; // namespace sock