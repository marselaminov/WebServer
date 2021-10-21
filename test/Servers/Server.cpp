//
// Created by Maya Queen on 10/21/21.
//

#include "Server.hpp"

Server::~Server() {
	delete _socket;
}

Server::Server(int domain, int type, int protocol, int port, unsigned long addr, int bcklg)
{
	_socket = new ServerSocket(domain, type, protocol, port, addr, bcklg);
}

ServerSocket *Server::get_socket() {
	return _socket;
}