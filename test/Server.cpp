//
// Created by lexa on 02.11.2021.
//

#include "Server.hpp"

Server::Server() {
	_host = "127.0.0.1";
	_port = 5555;
}

void Server::createSocket() {
	if ((_socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw std::runtime_error("fatal error! socket!");
	bzero(&_sockAddr, sizeof(_sockAddr));

	_sockAddr.sin_family = AF_INET;
	_sockAddr.sin_addr.s_addr =  htonl(INADDR_ANY);
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

//	if (fcntl(_socketFd, F_SETFL, O_NONBLOCK) < 0) {
//		if (close(_socketFd) < 0){
//			throw std::runtime_error("Close error!");
//		}
//		throw std::runtime_error("Fcntl error!");
//		return ;
//	}
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

const sockaddr_in &Server::getSockAddr() const {
	return _sockAddr;
}

void Server::setSockAddr(const sockaddr_in &sockAddr) {
	_sockAddr = sockAddr;
}

const std::map<std::string, t_location> &Server::getLocation() const {
	return _location;
}

void Server::setLocation(const std::map<std::string, t_location> &location) {
	_location = location;
}

const std::string &Server::getServerName() const {
	return _serverName;
}

void Server::setServerName(const std::string &serverName) {
	_serverName = serverName;
}

const std::string &Server::getHost() const {
	return _host;
}

void Server::setHost(const std::string &host) {
	_host = host;
}

const std::string &Server::getErrorPage() const {
	return _errorPage;
}

void Server::setErrorPage(const std::string &errorPage) {
	std::string errorCode = errorPage.substr(0, 3);
	std::string errorPath = errorPage.substr(4);
	this->_errorPage = errorPath;
	this->_errorPageCode = std::stoi(errorCode);
}

unsigned int Server::getPort() const {
	return _port;
}

void Server::setPort(const std::string &port) {
	int cast = std::stoi(port);
	try {
		this->_port = static_cast<unsigned int>(cast);
		if (port.size() != std::to_string(this->_port).size())
			throw std::exception();
	}
	catch (std::exception &e) {
		std::cout << "Error port in config file" << std::endl;
	}
}

int Server::getErrorPageCode() const {
	return _errorPageCode;
}

void Server::setErrorPageCode(int errorPageCode) {
	_errorPageCode = errorPageCode;
}

const std::string &Server::getAuthBasicUserFile() const {
	return _auth_basic_user_file;
}

void Server::setAuthBasicUserFile(const std::string &authBasicUserFile) {
	_auth_basic_user_file = authBasicUserFile;
}