//
// Created by Legate Gunship on 11/10/21.
//

#include "Client.hpp"

Client::Client(const sockaddr_in &addr, unsigned int port, const std::string &host, int socketFd)
: addr(addr), port(port), host(host), socketFd(socketFd)
{
	_send_pos = 0;
	_state = READ_REQ;
	this->request = new HttpRequest();
	this->response = new HttpResponse();
	this->infoClient = new char[100];
	socklen_t len = sizeof(sockaddr_in);

	if (!inet_ntop(AF_INET, &this->addr, this->infoClient, len))
		std::cerr << "Error: Client:  inet_ntop" << std::endl;
}

Client::~Client() {
	std::cout << MAGENTA << "End of connection (SocketFD = " << this->socketFd << ")" << RESET << std::endl;

	shutdown(this->socketFd, SHUT_WR); // блокируем(прекращаем) передачу данных для сокета, но сам сокет уничтожаем следующим действием
	close(this->socketFd); // закрываем сокет
	delete this->request;
	delete this->response;
	delete this->infoClient;
}

/* SETTERS */

void Client::setRequest(HttpRequest *request) {
	Client::request = request;
}

void Client::setResponse(HttpResponse *response) {
	Client::response = response;
}

//void Client::setFlag(int flag) {
//	_flag = flag;
//}

void Client::setState(States state) {
	_state = state;
}

void Client::setSendPos(ssize_t pos) {
	_send_pos = pos;
}

/* GETTERS */

char *Client::getInfoClient() const {
	return infoClient;
}

//int Client::getFlag() const {
//	return _flag;
//}

States Client::getState() {
	return _state;
}

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

ssize_t Client::getSendPos() {
	return _send_pos;
}


