#pragma once

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include "common_windows.h"

// Need to link with Ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

namespace sock
{

int listen(UniversalSocket &listen_socket, uint16_t port)
{
    int i_result;
    struct addrinfo hints;
    struct addrinfo *result = NULL;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    i_result = getaddrinfo(NULL, std::to_string(port).c_str(), &hints, &result);

    if (i_result != 0)
    {
        printf("cancer\n");
        fprintf(stderr, "getaddrinfo failed with error: %d\n", i_result);
        WSACleanup();
        return -1;
    }

    listen_socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (listen_socket == INV_SOCK)
    {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return -2;
    }

    // Setup the TCP listening socket
    i_result = bind(listen_socket, result->ai_addr, (int)result->ai_addrlen);
    if (i_result == SOCKET_ERROR)
    {
        fprintf(stderr, "bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(listen_socket);
        WSACleanup();
        return -3;
    }

    freeaddrinfo(result);

    i_result = ::listen(listen_socket, SOMAXCONN);
    if (i_result == SOCKET_ERROR)
    {
        fprintf(stderr, "listen failed with error: %d\n", WSAGetLastError());
        closesocket(listen_socket);
        WSACleanup();
        return -4;
    }

    return 0;
}

UniversalSocket accept(UniversalSocket &listen_socket)
{
    UniversalSocket client_socket = ::accept(listen_socket, NULL, NULL);
    if (client_socket == INV_SOCK)
    {
        fprintf(stderr, "accept failed with error: %d\n", WSAGetLastError());
        closesocket(listen_socket);
        WSACleanup();
        return INV_SOCK;
    }

    return client_socket;
}
}; // namespace sock