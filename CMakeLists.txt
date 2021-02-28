cmake_minimum_required (VERSION 3.0)

project(CPLUSPLUS)

# Set up C++17, and group binaries and libraries in a folder
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_subdirectory(tcp)
