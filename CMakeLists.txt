cmake_minimum_required(VERSION 3.14)
project(projetblockchain C)

set(CMAKE_C_STANDARD 99)

add_executable(projetblockchain main.c blockchain.h blockchain.c)
find_package(OpenSSL REQUIRED)
target_link_libraries(projetblockchain OpenSSL::SSL)