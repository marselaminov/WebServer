//
// Created by Legate Gunship on 10/27/21.
//

#include "Server.hpp"

Server::Server() {}

Server::~Server() {}

const sockaddr_in &Server::getSockAddr() const {
	return sockAddr;
}

void Server::setSockAddr(const sockaddr_in &sockAddr) {
	Server::sockAddr = sockAddr;
}

const std::map<std::string, t_location> &Server::getLocation() const {
	return location;
}

void Server::setLocation(const std::map<std::string, t_location> &location) {
	Server::location = location;
}

const std::string &Server::getServerName() const {
	return serverName;
}

void Server::setServerName(const std::string &serverName) {
	Server::serverName = serverName;
}

const std::string &Server::getHost() const {
	return host;
}

void Server::setHost(const std::string &host) {
	Server::host = host;
}

const std::string &Server::getErrorPage() const {
	return errorPage;
}

void Server::setErrorPage(const std::string &errorPage) {
	std::string errorCode = errorPage.substr(0, 3);
	std::string errorPath = errorPage.substr(4);
	this->errorPage = errorPath;
	this->errorPageCode = std::stoi(errorCode);
}

unsigned int Server::getPort() const {
	return port;
}

void Server::setPort(const std::string &port) {
	int cast = std::stoi(port);
	try {
		this->port = static_cast<unsigned int>(cast);
		if (port.size() != std::to_string(this->port).size())
			throw std::exception();
	}
	catch (std::exception &e) {
		std::cout << "Error port in config file" << std::endl;
	}
}

int Server::getErrorPageCode() const {
	return errorPageCode;
}

void Server::setErrorPageCode(int errorPageCode) {
	Server::errorPageCode = errorPageCode;
}

int Server::getSocketFd() const {
	return socketFd;
}

int	Server::createSocket() {}

const std::string &Server::getAuthBasicUserFile() const {
	return auth_basic_user_file;
}

void Server::setAuthBasicUserFile(const std::string &authBasicUserFile) {
	auth_basic_user_file = authBasicUserFile;
}




