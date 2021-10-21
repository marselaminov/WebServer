//
// Created by Maya Queen on 10/21/21.
//

#ifndef WEBSERV_SERVERSOCKET_HPP
#define WEBSERV_SERVERSOCKET_HPP

#include "ASocket.hpp"

class ServerSocket : public ASocket
{
public:
	ServerSocket(int domain, int type, int protocol, int port, unsigned long addr, int bcklg);

	int connect(int sock, struct sockaddr_in address);
	int start_listening();
private:
	int _backlog;
};


#endif //WEBSERV_SERVERSOCKET_HPP
