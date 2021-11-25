//
// Created by lexa on 02.11.2021.
//

#include "../includes/Server.hpp"

Server::Server() {
}

void Server::createSocket() {
	// создание сокета
	if ((_socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		throw std::runtime_error("fatal error! socket!");


	// предотвращаем "залипания" нашего порта
	int opt = 1;
	if (setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		if (close(_socketFd) < 0)
			throw std::runtime_error("Close error!");
		throw std::runtime_error("Setsockopt error!");
	}


	// снабжаем сокет собственным адресом
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr)); // зануляем элементы структуры , чтобы инициализировать самостоятельно
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(_host.c_str());
	addr.sin_port = htons(_port);
	int addrlen = sizeof(addr);
	if ((bind(_socketFd, (struct sockaddr *) &addr, addrlen)) == -1) {
		if (close(_socketFd) < 0)
			throw std::runtime_error("Close error!");
		throw std::runtime_error("Bind error!");
	}


	// перевод слушающего сокета в неблокирующий режим
	if (fcntl(_socketFd, F_SETFL, O_NONBLOCK) == -1) {
		if (close(_socketFd) < 0)
			throw std::runtime_error("Close error!");
		throw std::runtime_error("Fcntl error!");
	}


	// делаем сокет слушающим, на сокете в слушающем состоянии можно только принять или не принять соединение
	if (listen(_socketFd, BACKLOG) == -1) {
		if (close(_socketFd) < 0)
			throw std::runtime_error("Close error!");
		throw std::runtime_error("Listen error!");
	}
}

int Server::get_sockFd() const {
	return _socketFd;
}

const std::map<std::string, t_location> &Server::getLocation() const {
	return _location;
}

void Server::setLocation(const std::map<std::string, t_location> &location) {
	_location = location;
}

void Server::setServerName(const std::string &serverName) {
	_serverName = serverName;
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

std::string Server::getHost() const {
	return _host;
}

const std::string &Server::getServerName() const {
	return _serverName;
}
