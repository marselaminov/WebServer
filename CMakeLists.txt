cmake_minimum_required(VERSION 3.19)
project(WebServer)

set(CMAKE_CXX_STANDARD 14)

<<<<<<< HEAD
include_directories(test)
=======
>>>>>>> cec4237d7860b91c54eace71078ba2793a7fd37f
include_directories(test/HTTP)
include_directories(test/Servers)
include_directories(test/Sockets)

add_executable(WebServer
        test/HTTP/HttpRequest.cpp
        test/HTTP/HttpRequest.hpp
<<<<<<< HEAD
        test/HTTP/HttpResponse.cpp
        test/HTTP/HttpResponse.hpp
=======
>>>>>>> cec4237d7860b91c54eace71078ba2793a7fd37f
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
<<<<<<< HEAD
        test/main.cpp
        test/Parser.cpp
        test/Parser.hpp
        test/Server.cpp
        test/Server.hpp
        test/WebServer.cpp
        test/WebServer.hpp)
=======
        test/main.cpp test/HTTP/HttpResponse.cpp test/HTTP/HttpResponse.hpp test/WebServer.cpp test/WebServer.hpp
        test/Server.cpp test/Server.hpp test/Parser.hpp test/Parser.cpp)
>>>>>>> cec4237d7860b91c54eace71078ba2793a7fd37f
