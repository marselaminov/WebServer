#ifndef WEBSERV_SOCKET_HPP
#define WEBSERV_SOCKET_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

class ASocket {
public:
	//Default constructor
	ASocket(int domain, int type, int protocol, int port, unsigned long addr);
    virtual ~Socket();

    //connect socket
    virtual int connect(int sock, struct sockaddr_in address) = 0;

    //GET functions
	int get_sock();
	struct sockaddr_in get_address();

private:
	int _sock_fd;
	struct sockaddr_in _address;
};


#endif //WEBSERV_SOCKET_HPP
