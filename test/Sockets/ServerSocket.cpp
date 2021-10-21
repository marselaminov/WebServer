//
// Created by Maya Queen on 10/21/21.
//

#include "ServerSocket.hpp"
//Default constructor
ServerSocket::ServerSocket(int domain, int type, int protocol, int port, unsigned long addr)
: ASocket(domain, type, protocol, port, addr)
{
	if ((connect(get_sock(), get_address())) < 0)
		throw (std::runtime_error("bind error\n"));
}

//binding socket
int ServerSocket::connect(int sock, struct sockaddr_in address) {
	return bind(sock, (struct sockaddr_in *)&address, sizeof(address));
}
