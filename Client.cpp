//
// Created by Legate Gunship on 11/10/21.
//

#include "Client.hpp"


HttpRequest *Client::getRequest() {
	return request;
}

HttpResponse *Client::getResponse() {
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

Client::Client(const sockaddr_in &addr, unsigned int port, const std::string &host, int socketFd)
: addr(addr), port(port), host(host), socketFd(socketFd)
{
	_flag = _Client___Ready_To_Read;
	this->request = new HttpRequest();
	this->response = new HttpResponse();
	this->infoClient = new char[100];
	socklen_t len = sizeof(sockaddr_in);
//	inet_ntop(this->socketFd, &this->addr, this->infoClient, len);

	if (!inet_ntop(AF_INET, &this->addr, this->infoClient, len))
//		throw (std::runtime_error(RED "Error inet_ntop" RESET));
		std::cerr << "Error inet_ntop" << std::endl;
}

char *Client::getInfoClient() const {
	return infoClient;
}

Client::~Client() {
	std::cout << MAGENTA << "End of connection (SocketFD = " << this->socketFd << ")" << RESET << std::endl;

	shutdown(this->socketFd, SHUT_WR); // блокируем(прекращаем) передачу данных для сокета, но сам сокет уничтожаем следующим действием
	close(this->socketFd); // закрываем сокет
	delete this->request;
	delete this->response;
	delete this->infoClient;
}

void Client::setRequest(HttpRequest *request) {
	Client::request = request;
}

void Client::setResponse(HttpResponse *response) {
	Client::response = response;
}

int Client::getFlag() const {
	return _flag;
}

void Client::setFlag(int flag) {
	_flag = flag;
}
