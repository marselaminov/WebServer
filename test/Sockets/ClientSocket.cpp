//
// Created by Maya Queen on 10/21/21.
//

#include "ClientSocket.hpp"

ClientSocket::ClientSocket(int domain, int type, int protocol, int port, unsigned long addr)
: ASocket(domain, type, protocol, port, addr)
{
	if ((connect(get_sock_fd(), get_address())) < 0)
		throw (std::runtime_error("ClientSocket: connect error\n"));
}

int ClientSocket::connect(int sock, struct sockaddr_in address) {
	return ::connect(sock, reinterpret_cast<const sockaddr *>(&address), sizeof(address));
}
