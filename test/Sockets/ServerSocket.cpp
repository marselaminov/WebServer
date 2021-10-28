//
// Created by Maya Queen on 10/21/21.
//

#include "ServerSocket.hpp"
//Default constructor
ServerSocket::ServerSocket(int domain, int type, int protocol, int port, unsigned long addr, int bcklg)
: ASocket(domain, type, protocol, port, addr), _backlog(bcklg)
{
	if ((connect(get_sock_fd(), get_address())) < 0)
		throw (std::runtime_error("ServerSocket: bind error"));
	if ((start_listening()) < 0)
		throw (std::runtime_error("ServerSocket: listen error"));
}

//binding socket
int ServerSocket::connect(int sock, struct sockaddr_in address) {
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	return ::bind(sock, (struct sockaddr *)(&address), (socklen_t)sizeof(address));
}

//listening

int ServerSocket::start_listening() {
	return listen(get_sock_fd(), this->_backlog);
}