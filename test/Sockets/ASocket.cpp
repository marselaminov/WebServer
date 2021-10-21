#include "ASocket.hpp"

//Default constructor

ASocket::ASocket(int domain, int type, int protocol, int port, unsigned long addr)
{
//initializing sock struct
	this->_address.sin_family = domain;
	this->_address.sin_port = htons(port);
	this->_address.sin_addr.s_addr = htonl(addr);
//crate sock
	if ((this->_sock_fd = socket(domain, type, protocol)) <= 0)
		throw (std::runtime_error("Socket error\n"));
//connect socket
//if ((connect(this->_sock_fd, this->_address)) < 0)
//		throw (std::runtime_error("Socket error\n"));
}

//GET functions

struct sockaddr_in ASocket::get_address() {
	return _address;
}

int ASocket::get_sock_fd() {
	return _sock_fd;
}