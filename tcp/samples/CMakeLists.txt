cmake_minimum_required (VERSION 3.0)

project(tcp)

add_executable(client src/client.cpp)
add_executable(server src/server.cpp)
add_executable(primersocket src/main_primer_socket.cpp)