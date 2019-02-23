/*
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        To compile in windows using g++, u 
        need to add this flags to g++ cmd:

                    -lws2_32
    !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/

#include "universal_client.h"

int main()
{
    sock::init(); // init WSADATA in windows

    sock::UniversalSocket s; // declare our socket so we have a way to connect.
                             // This is equivalent with declaring a file descriptor
                             // int fd = 0;

    int res = sock::connect(s, "localhost", 5555); // connect to `localhost` on port 55555
                                                   // this is equivalent with an open(fd)
                                                   // localhost is our computer. We coud
                                                   // have connected to `google.ro` for example
                                                   // or to `8.8.8.8`
    if (res)                                       // check for errors
    {
        fprintf(stderr, "connect failed with %d\n", res);
        sock::uninit(s);
        return -1;
    }
    else
    {
        printf("connect succes!\n");
    }

    std::string payload = "asd"; // prepare our message

    res = sock::send(s, payload); // send our message to the server we connected to
                                  // this is equivalent to a write

    if (res < 0) // check for errors
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

    res = sock::recv(s, recv_buf, 99); // receive our message from the server
                                       // this is equivalent to a read
                                       // not that this call to recv will return
                                       // the number of bytes received from server
                                       // this can be < 99.
                                       // Also very important: this call to recv is
                                       // blocking until we receive somentring from
                                       // the network. So in case the server doesnt
                                       // send anything back, we are blocked here
    recv_buf[100] = '\0';

    if (res < 0) // check for errors
    {
        fprintf(stderr, "recv failed with %d\n", res);
        sock::uninit(s);
        return -1;
    }
    else
    {
        printf("Got response from server: %s\n", recv_buf);
    }

    sock::disconnect(s); // disconnect
                         // this is equivalent to a close

    sock::uninit(s); // uninit WSADATA
}