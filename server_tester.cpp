/*
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        To compile in windows using g++, u 
        need to add this flags to gcc cmd:

                    -lws2_32
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

#include "universal_server.h"

int main()
{
    sock::init();

    sock::UniversalSocket s;

    int res = sock::listen(s, 5555);

    if (res)
    {
        fprintf(stderr, "listen failed with %d\n", res);
        sock::uninit(s);
        return -1;
    }
    else
    {
        printf("listen succes!\n");
    }

    sock::UniversalSocket client = sock::accept(s);

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