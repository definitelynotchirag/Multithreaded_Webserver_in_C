# Multithreaded Web Server in C

This project contains implementations of an HTTP proxy server with caching, a simple web server, and socket programming examples for client-server communication.

## Project Structure

```
.vscode/
    settings.json
c.html
client
index.html
proxy_parse.c
proxy_parse.h
proxy_server_with_cache.c
server
socket_prog/
    client.c
    server.c
webserver
webserver_prog/
    temp.c
    webserver.c
```

## Files and Directories

- **.vscode/settings.json**: Configuration for Visual Studio Code to associate certain file extensions with the C language.
- **c.html**: A simple HTML file.
- **client**: Empty file.
- **index.html**: Another simple HTML file.
- **proxy_parse.c**: Implementation of an HTTP request parsing library.
- **proxy_parse.h**: Header file for the HTTP request parsing library.
- **proxy_server_with_cache.c**: Incomplete implementation of a proxy server with caching.
- **server**: Empty file.
- **socket_prog/**: Directory containing client and server implementations for socket programming.
  - **client.c**: Implementation of a simple client that connects to a server and sends a message.
  - **server.c**: Implementation of a simple server that accepts connections from clients and processes messages.
- **webserver**: Empty file.
- **webserver_prog/**: Directory containing web server implementations.
  - **temp.c**: Implementation of a simple web server that responds with a static HTML page.
  - **webserver.c**: Implementation of a multi-threaded web server using semaphores for synchronization.

## How to Build and Run

### Building the Project

To build the project, you can use `gcc` to compile the C files. Here are some examples:

```sh
# Compile the HTTP request parsing library
gcc -o proxy_parse proxy_parse.c

# Compile the socket programming client and server
gcc -o socket_client socket_prog/client.c
gcc -o socket_server socket_prog/server.c

# Compile the simple web server
gcc -o webserver_prog/temp webserver_prog/temp.c

# Compile the multi-threaded web server
gcc -o webserver_prog/webserver webserver_prog/webserver.c -lpthread
```

### Running the Programs

#### HTTP Request Parsing Library

The HTTP request parsing library is used internally by the proxy server. You can include it in your own projects by including 

proxy_parse.h

 and linking against the compiled object file.

#### Socket Programming Client and Server

To run the socket programming examples:

1. Start the server:
   ```sh
   ./socket_server <port>
   ```
2. In another terminal, start the client:
   ```sh
   ./socket_client <hostname> <port>
   ```

#### Simple Web Server

To run the simple web server:

```sh
./webserver_prog/temp
```

#### Multi-threaded Web Server

To run the multi-threaded web server:

```sh
./webserver_prog/webserver
```

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Authors

- Matvey Arye (HTTP Request Parsing Library)
- Other contributors for various parts of the project.

## Acknowledgments

- COS 461 and COS 518 courses for providing the initial code and inspiration for this project.

---

