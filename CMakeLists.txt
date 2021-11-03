cmake_minimum_required(VERSION 3.19)
project(WebServer)

set(CMAKE_CXX_STANDARD 14)

include_directories(test/HTTP)
include_directories(test/Servers)
include_directories(test/Sockets)

add_executable(WebServer
        test/HTTP/HttpRequest.cpp
        test/HTTP/HttpRequest.hpp
        test/Servers/Server.cpp
        test/Servers/Server.hpp
        test/Servers/TestServer.cpp
        test/Servers/TestServer.hpp
        test/Sockets/ASocket.cpp
        test/Sockets/ASocket.hpp
        test/Sockets/ClientSocket.cpp
        test/Sockets/ClientSocket.hpp
        test/Sockets/ServerSocket.cpp
        test/Sockets/ServerSocket.hpp
        test/main.cpp test/HTTP/HttpResponse.cpp test/HTTP/HttpResponse.hpp test/WebServer.cpp test/WebServer.hpp
        test/Server.cpp test/Server.hpp test/Parser.hpp test/Parser.cpp)
