cmake_minimum_required(VERSION 3.17)
project(SNAKE C)

set(CMAKE_C_STANDARD 90)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")
add_executable(SNAKE main.c)