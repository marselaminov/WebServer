//
// Created by lexa on 02.11.2021.
//

#include "Server.hpp"

Server::Server() {

}

void Server::createSocket() {
	if ((_socketFd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("fatal error! socket!");
	bzero(&_sockAddr, sizeof(_sockAddr));

	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr.s_addr = inet_addr(_host.c_str());
	_sockAddr.sin_port = htons(_port);
	int yes = 1;

	if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		if (close(_socketFd) < 0) {
			throw std::runtime_error("Close error!");
		}
		throw std::runtime_error("Setsockopt error!");
	}

	if ((bind(_socketFd, (struct sockaddr * )&_sockAddr, sizeof _sockAddr)) < 0){
		if (close(_socketFd) < 0) {
			throw std::runtime_error("Close error!");
		}
		throw std::runtime_error("Bind error!");
	}

	if (fcntl(_socketFd, F_SETFL, O_NONBLOCK) < 0) {
		if (close(_socketFd) < 0){
			throw std::runtime_error("Close error!");
		}
		throw std::runtime_error("Fcntl error!");
		return ;
	}
	if (listen(_socketFd, BACKLOG) < 0){
		if (close(_socketFd) < 0){
			throw std::runtime_error("Close error!");
		}
		throw std::runtime_error("Listen error!");
	}
	return ;
}

sockaddr_in Server::get_sockAddr() {
	return _sockAddr;
}

int Server::get_sockFd() {
	return _socketFd;
}