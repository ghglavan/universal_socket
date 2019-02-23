/*
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        To compile in windows using g++, u 
        need to add this flags to g++ cmd:

                    -lws2_32
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

#include "universal_server.h"

int main()
{
    sock::init(); // init WSADATA

    sock::UniversalSocket s; // declare our socket so we have a way to listen for connections.
                             // This is equivalent with declaring a file descriptor
                             // int fd = 0;

    int res = sock::listen(s, 5555); // start listening for new connections on port 5555

    if (res) // check for errors
    {
        fprintf(stderr, "listen failed with %d\n", res);
        sock::uninit(s);
        return -1;
    }
    else
    {
        printf("listen succes!\n");
    }

    sock::UniversalSocket client = sock::accept(s); // accept a new connection
                                                    // this call to accept will return a new
                                                    // UniversalSocket that we can use as a connected socket
                                                    // note that s (our listening socket) is used only to listen
                                                    // for new connection. Once we have one, we can read and write
                                                    // to our new created socket.
                                                    // Also very important: this call to accept is blocking until
                                                    // a client is `connect`-ing to our server. We can wait here
                                                    // forever

    // from here on, everything is the same as in client_tester. Only the order of read and write differs.
    // If you want to check the comments, go to client_tester.cpp because i'm too lazy to copy them here :D

    if (client == sock::INV_SOCK)
    {
        fprintf(stderr, "accept failed with %d\n", res);
        sock::uninit(s);
        return -1;
    }
    else
    {
        printf("accept succes!\n");
    }
    char recv_buf[100];

    res = sock::recv(client, recv_buf, 99);
    recv_buf[100] = '\0';

    if (res < 0)
    {
        fprintf(stderr, "recv failed with %d\n", res);
        sock::uninit(s);
        return -1;
    }
    else
    {
        printf("Got message from client: %s\n", recv_buf);
    }

    std::string resp(recv_buf);

    res = sock::send(client, resp);

    if (res < 0)
    {
        fprintf(stderr, "send failed with %d\n", res);
        sock::uninit(s);
        return -1;
    }
    else
    {
        printf("send success\n");
    }
    sock::disconnect(s);

    sock::uninit(s);
}