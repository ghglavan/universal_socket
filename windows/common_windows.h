#pragma once
#define _WIN32_WINNT 0x501

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <string>

namespace sock
{

typedef SOCKET UniversalSocket;

UniversalSocket INV_SOCK = INVALID_SOCKET;

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
    if (connect_socket != INV_SOCK)
        closesocket(connect_socket);

    WSACleanup();
    return 0;
};

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
    return i_result;
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
}; // namespace sock
