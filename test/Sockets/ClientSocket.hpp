//
// Created by Maya Queen on 10/21/21.
//

#ifndef WEBSERV_CLIENTSOCKET_HPP
#define WEBSERV_CLIENTSOCKET_HPP

#include "ASocket.hpp"

class ClientSocket : public ASocket{
public:
	ClientSocket(int domain, int type, int protocol, int port, unsigned long addr);

	int connect(int sock, struct sockaddr_in address);
};


#endif //WEBSERV_CLIENTSOCKET_HPP
