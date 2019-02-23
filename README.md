# universal_socket

```
For windows: if you compile with VC++, everything should work just file, if you compile with g++, you need -lws2_32
```

## API:
   ### You can think of an UniversalSocket as a file descriptor, you can `open` it (`listen`, `connect`), you can `read` from it (`recv`), you can `write` to it (`send`), you can `close` it (`disconnect`, `close_read`)

   * Common:
      ```C++
      int init() // NOP in linux, init WSADATA in windows
      ```
      `init` returns < 0 on error, 0 on success.
      
      ```C++
      int uninit() // NOP in linux, uninit WSADATA in windows
      ```
      `uninit` returns < 0 on error, 0 on success.
      
      ```C++
      int send(UniversalSocket &connect_socket, std::string s) // send string `s` using `connect_socket`
      ```
      `send` returns < 0 on error, 0 on success.
      
      ```C++
      int recv(UniversalSocket &connect_socket, char *recvbuf, size_t count) // recv `count` bytes into `recv_buf` from `connect_socket`
      ```
      `recv` returns < 0 on error, 0 on success. `recv` is blocking.
      
      ```C++
      int disconnect(UniversalSocket &connect_socket) // close(diconnect) connect_socket
      ```
      `disconnect` returns < 0 on error, 0 on success.
      
      ```C++
      int close_read(UniversalSocket &connect_socket) // NOP in linux, close reading end of `connect_sock` in windows
      ```
      `close_read` returns < 0 on error, 0 on success.
   
   
   * Server specific:
      ```C++
      int listen(UniversalSocket &listen_socket, uint16_t port) // listen with `listen_sock` on port `port`
      ```
      `listen` returns < 0 on error, 0 on success.
      
      ```C++
      UniversalSocket accept(UniversalSocket &listen_socket) //  accept a new `UniversalSocket` from listening socket `listen_socket`
      ```
      `accept` returns `INV_SOCK` on error, a new UnivesalSocket that can be used with `send`, `reacv`, `disconnect` on success.
      `INV_SOCK` is a global variable: `UniversalSocket INV_SOCK = INVALID_SOCKET;` in windows `UniversalSocket INV_SOCK = -1;` in linux
      
   * Client specific:
      ```C++
      int connect(UniversalSocket &connect_socket, std::string server_name, uint16_t port) // connect `connect_socket` to the server specified by `servername` and port `port`
      ```
      `connect` returns < 0 on error, 0 on success.
      ```
      
## you can find examples in `client_tester.cpp` and `server_tester.cpp`
      
