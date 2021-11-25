cmake_minimum_required(VERSION 3.19)
project(WebServer)

set(CMAKE_CXX_STANDARD 14)

include_directories(HTTP)

add_executable(WebServer
        srcs/HttpRequest.cpp
        includes/HttpRequest.hpp
        srcs/main.cpp
        srcs/HttpResponse.cpp
        includes/HttpResponse.hpp
        srcs/AutoIndex.cpp
        srcs/WebServer.cpp
        includes/WebServer.hpp
        srcs/Server.cpp
        includes/Server.hpp
        includes/Parser.hpp
        srcs/Parser.cpp  srcs/ChunkedRequest.cpp includes/ChunkedRequest.hpp
        srcs/Client.cpp
        includes/Client.hpp
        srcs/CGI.cpp
        includes/CGI.hpp)
