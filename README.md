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
      `accept` returns `INV_SOCK` on error, a new connected UnivesalSocket that can be used with `send`, `reacv`, `disconnect` on success.
      `INV_SOCK` is a global variable: `UniversalSocket INV_SOCK = INVALID_SOCKET;` in windows `UniversalSocket INV_SOCK = -1;` in linux
      
   * Client specific:
      ```C++
      int connect(UniversalSocket &connect_socket, std::string server_name, uint16_t port) // connect `connect_socket` to the server specified by `servername` and port `port`
      ```
      `connect` returns < 0 on error, 0 on success.
      ```
      
### You can find documented examples in `client_tester.cpp` and `server_tester.cpp`
   Notice that the differences between server and client are in initialization. Once we have a connected socket, everything is the same. A socket we are `listen`ing to is called a listen socket. The only operation we can do on this socket is `accept`, which returns a new connected UniversalSocket.
   

## Your tasks:
   * A class that is not instantiable is a class that has all constructors protected except for copy and move constructors or has a pure virtual function. The method with protected constructors is not exactly not instantiable because you can create an object from a class with protected constructors via a firend function or class, or via inheritance, but its good enough when we dont have pure virtual functions
   * A class that cannot be constructed is a class that has all constructors protected excet for copy and move constructors.

   - [ ] create a class _SocketInits_ that cannot be instantiated for our sockets with methods for `init`, `uninit`, `disconnect` and `close_read`
   - [ ] create a class _Socket_ that cannot be instantiated with ***virtual*** methods for `send`, `recv`.
   - [ ] create a class for _ConnectSocket_, that inherits _SocketInits_ and _Socket_, overrides `send` and `recv` and defines `connect`. `connect` should return a _ConnectedSocket_ (see next task).
   - [ ] create a class forr _ConnectedSocket_, that inherits _ConnectSocket_ and cannot be constructed.
   - [ ] create a class for _ListenSocket_,  with methods for `listen` and `accept`. `accept` will return a new _ConnectedSocket_
   
   ``` 
   More to come
   ```
