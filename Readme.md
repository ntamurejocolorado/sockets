# Sockets in C++

This is a mini project where there's a socket server and client.
Type: TCP.

## Files

- client.cpp: It's the client for server.cpp
- server.cpp
- main_primer_socket.cpp: It's only server followed a tutorial. If you want to use this, you can continue reading.

## Usage

### Compiling

* At the root folder:

```bash
mkdir build && cd build
cmake ..
make 
```

## How to use client.cpp and server.cpp

From terminal in the folder build, you can write:

```bash
./bin/server
``` 

The server will be activated, after that in other terminal, we'll activate client:

```bash
./bin/client
```

The client is activated, and you can write strings which will be send to server.

## How to use main_primer_socket.cpp

This server can be launched and listening. So, in the terminal:

```bash
./bin/primer_socket
```

After that, you can use like client for example ```telnet localhost port``` in other terminal.

## Author

ntamurejo <noelia.tc89@gmail.com>


