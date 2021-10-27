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

const std::string &Server::getRoot() const {
	return root;
}

void Server::setRoot(const std::string &root) {
	Server::root = root;
}

const std::string &Server::getErrorPage() const {
	return errorPage;
}

void Server::setErrorPage(const std::string &errorPage) {
	Server::errorPage = errorPage;
}

unsigned int Server::getPort() const {
	return port;
}

void Server::setPort(unsigned int port) {
	Server::port = port;
}

unsigned int Server::getClientMaxBodySize() const {
	return client_max_body_size;
}

void Server::setClientMaxBodySize(unsigned int clientMaxBodySize) {
	client_max_body_size = clientMaxBodySize;
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




