#pragma once

#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

namespace sock
{
typedef int UniversalSocket;

UniversalSocket INV_SOCK = -1;

int init() { return 0; }
int uninit(UniversalSocket &) { return 0; }

int send(UniversalSocket &connect_socket, std::string s)
{
    int i_result = ::send(connect_socket, s.c_str(), s.size(), 0);

    if (i_result == -1)
        perror("Error in send: ");

    return i_result;
}

int recv(UniversalSocket &connect_socket, char *recv_buff, size_t count)
{
    int i_result = ::recv(connect_socket, recv_buff, count, 0);

    if (i_result == -1)
        perror("Error in recv: ");

    return i_result;
}

int disconnect(UniversalSocket &connect_socket)
{
    close(connect_socket);
    return 0;
}

int close_read(UniversalSocket &connect_socket)
{
    return 0;
}

}; // namespace sock
