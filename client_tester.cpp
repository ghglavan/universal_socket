/*
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        To compile in windows using gcc, u 
        need to add this flags to gcc cmd:

                    -lws2_32
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

#include "client_windows.h"

int main()
{
    sock::init();

    sock::UniversalSocket s;

    int res = sock::connect(s, "localhost", 5555);

    if (res)
    {
        fprintf(stderr, "connect failed with %d\n", res);
        sock::uninit(s);
        return -1;
    }
    else
    {
        printf("connect succes!\n");
    }

    std::string payload = "asd";

    res = sock::send(s, payload);

    if (res)
    {
        fprintf(stderr, "send failed with %d\n", res);
        sock::uninit(s);
        return -1;
    }
    else
    {
        printf("send succes!\n");
    }

    char recv_buf[100];

    res = sock::recv(s, recv_buf, 99);
    recv_buf[100] = '\0';

    if (res)
    {
        fprintf(stderr, "recv failed with %d\n", res);
        sock::uninit(s);
        return -1;
    }
    else
    {
        printf("Got response from server: %s", recv_buf);
    }

    sock::disconnect(s);

    sock::uninit(s);
}