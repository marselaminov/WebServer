//
// Created by Legate Gunship on 11/10/21.
//

#include "Client.hpp"


HttpRequest *Client::getRequest() const {
	return request;
}

HttpResponse *Client::getResponse() const {
	return response;
}

unsigned int Client::getPort() const {
	return port;
}

const std::string &Client::getHost() const {
	return host;
}

int Client::getSocketFd() const {
	return socketFd;
}

Client::Client(const sockaddr_in &addr, unsigned int port, const std::string &host, int socketFd) : addr(addr),
																									port(port),
																									host(host),
																									socketFd(
																											socketFd) {
	this->request = new HttpRequest();
	this->response = new HttpResponse();
	this->infoClient = new char[20];
	socklen_t len = sizeof(sockaddr_in);

	if (!inet_ntop(this->socketFd, &addr, infoClient, len))
		throw (std::runtime_error(RED "Error inet_ntop" RESET));
//		std::cerr << "Error inet_ntop" << std::endl;
}

char *Client::getInfoClient() const {
	return infoClient;
}

Client::~Client() {
	std::cout << MAGENTA << "End of connection (SocketFD = " << this->socketFd << ")" << RESET << std::endl;

	shutdown(this->socketFd, 1); // блокируем передачу и получение данных для сокета
	close(this->socketFd); // закрываем сокет
	delete this->request;
	delete this->response;
	delete this->infoClient;
}
