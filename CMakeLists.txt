cmake_minimum_required(VERSION 3.19)
project(WebServer)

set(CMAKE_CXX_STANDARD 98)

add_executable(WebServer main.cpp Server.cpp Server.hpp Parser.cpp Parser.hpp)