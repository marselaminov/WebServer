#include "ASocket.hpp"

//Default constructor

Socket::ASocket(int domain, int type, int protocol, int port, unsigned long addr)
{
//crate sock
	if ((this->_sock_fd = socket(domain, type, protocol)) < 0)
		throw (std::runtime_error("Socket error\n"));
//initializing sock struct
	this->_address.sin_family = domain;
	this->_address.sin_port = port;
	this->_address.sin_addr = htonl(addr);
//connect socket
if ((connect(this->_sock_fd, this->_address)) < 0)
		throw (std::runtime_error("Socket error\n"));
}

//GET functions

struct sockaddr_in Socket::get_address() {
	return _address;
}

int Socket::get_sock() {
	return _sock_fd;
}