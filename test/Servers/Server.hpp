#ifndef WEBSERV_SERVER_HPP
#define WEBSERV_SERVER_HPP

#include "../Sockets/ServerSocket.hpp"
#include "../Sockets/ClientSocket.hpp"
#include <unistd.h>

class Server {
public:

	Server(int domain, int type, int protocol, int port,
		   unsigned long addr, int bcklg);
    virtual ~Server();

    virtual void launch() = 0;

    ServerSocket *get_socket();
private:
    ServerSocket * _socket;
    virtual void _acceptor() = 0;
    virtual void _handler() = 0;
    virtual void _responder() = 0;
};


#endif
