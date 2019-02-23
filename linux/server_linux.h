#pragma once

#include "common_linux.h"

namespace sock
{
int listen(UniversalSocket &listen_socket, uint16_t port)
{
    if ((listen_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("error in socket:");
        return -2;
    }

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    int opt_val = 1;
    setsockopt(listen_socket, SOL_SOCKET, SO_REUSEADDR, &opt_val, sizeof opt_val);

    int i_result = bind(listen_socket, (struct sockaddr *)&server, sizeof(server));

    if (i_result == -1)
    {
        perror("Error in bind: ");
        return -1;
    }

    i_result = ::listen(listen_socket, 128);

    if (i_result < 0)
    {
        perror("Error in listeb: ");
        return -2;
    }

    return 0;
}

UniversalSocket accept(UniversalSocket &listen_socket)
{
    struct sockaddr_in client;
    socklen_t client_len = sizeof(client);
    UniversalSocket client_socket = ::accept(listen_socket, (struct sockaddr *)&client, &client_len);

    if (client_socket < 0)
    {
        perror("Error in accept:");
        return INV_SOCK;
    }

    return client_socket;
}
}; // namespace sock