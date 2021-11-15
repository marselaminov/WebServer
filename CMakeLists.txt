cmake_minimum_required(VERSION 3.19)
project(WebServer)

set(CMAKE_CXX_STANDARD 14)

include_directories(HTTP)

add_executable(WebServer
        HTTP/HttpRequest.cpp
        HTTP/HttpRequest.hpp
        main.cpp
        HTTP/HttpResponse.cpp
        HTTP/HttpResponse.hpp
        HTTP/AutoIndex.cpp
        WebServer.cpp
        WebServer.hpp
        Server.cpp
        Server.hpp
        Parser.hpp
        Parser.cpp CGI.cpp CGI.hpp)
