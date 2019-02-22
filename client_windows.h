#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <string>
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Mswsock.lib")
#pragma comment(lib, "AdvApi32.lib")

typedef SOCKET UniversalSocket;

int init()
{
    WSADATA wsa_data;
    int i_result;

    i_result = WSAStartup(MAKEWORD(2, 2), &wsa_data);
    if (i_result != 0)
    {
        fprintf(stderr, "Error in wsa_startup with (blame windows!!). Error nr: %d", i_result);
        return -1;
    }
    return 0;
}

int uninit(UniversalSocket &connect_socket)
{
    if (connect_socket != INVALID_SOCKET)
        closesocket(connect_socket);

    WSACleanup();
    return 0;
};

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
        if (connect_socket == INVALID_SOCKET)
        {
            fprintf(stderr, "Error creating socket. Error nr: %d", i_result);
            uninit(connect_socket);
            return -2;
        }

        i_result = ::connect(connect_socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (i_result == SOCKET_ERROR)
        {
            closesocket(connect_socket);
            connect_socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (connect_socket == INVALID_SOCKET)
    {
        fprintf(stderr, "Unable to connect to server");
        uninit(connect_socket);
        return -3;
    }

    return 0;
}

int disconnect(UniversalSocket &connect_socket)
{
    closesocket(connect_socket);
    return 0;
}

int close_read(UniversalSocket &connect_socket)
{
    int i_result = shutdown(connect_socket, SD_SEND);
    if (i_result == SOCKET_ERROR)
    {
        fprintf(stderr, "Error closing socket. Error nr: ", i_result);
        uninit(connect_socket);
        WSACleanup();
        return -1;
    }
    return 0;
}

int send(UniversalSocket &connect_socket, std::string s)
{
    int i_result = ::send(connect_socket, s.c_str(), s.size(), 0);
    if (i_result == SOCKET_ERROR)
    {
        fprintf(stderr, "Send failed with error: %d", WSAGetLastError());
        uninit(connect_socket);
        WSACleanup();
        return -1;
    }
    return 0;
}

int recv(UniversalSocket &connect_socket, char *recvbuf, size_t count)
{
    int i_result;

    i_result = ::recv(connect_socket, recvbuf, count, 0);
    if (i_result == 0)
    {
        fprintf(stderr, "Connection closed");
        return -1;
    }
    else if (i_result < 0)
    {
        fprintf(stderr, "recv failed with error: %d\n", WSAGetLastError());
        return -2;
    }

    return 0;
}
