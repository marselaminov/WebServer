//
// Created by lexa on 02.11.2021.
//

#include "WebServer.hpp"

WebServer::WebServer() {
	Parser *parser;

	try {
		parser = new Parser("../test.conf");
	}
	catch (std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	_server = parser->getServers();
	delete parser;
}

void WebServer::start() {
	try {
		_server[0]->createSocket();
	}
	catch (std::exception &e) {
		std::cout << "ERROR: " << e.what() << std::endl;
	}
	life_cycle();
}


void WebServer::acceptor(fd_set &readFdSet, fd_set &writeFdSet) {

	for (size_t i = 0; i < _server.size(); ++i) {
		if (FD_ISSET(_server[i]->get_sockFd(), &readFdSet)) { // Проверяем сокеты серверов на наличие новых подключений
			struct sockaddr_in address;
			int addrlen = sizeof (address);
			int clientSocket;
			clientSocket = accept(_server[i]->get_sockFd(), (struct sockaddr *)&address, (socklen_t *)&addrlen);
			if (clientSocket < 0 || fcntl(clientSocket, F_SETFL, O_NONBLOCK) == -1) {
				if (close(clientSocket) < 0)
					throw std::runtime_error("Close error!");
				throw std::runtime_error("Fcntl error!");
			}
			_client.push_back(new Client(address, _server[i]->getPort(), _server[i]->getHost(), clientSocket));
			std::cout 	<< YELLOW << "Client with ip " << RED << _client.back()->getInfoClient()
						 << YELLOW <<  " connected! " << MAGENTA << "FD = " << clientSocket << RESET << std::endl;
		}
	}
}

void WebServer::handler(fd_set &readFdSet, fd_set &writeFdSet) {
	for (int i = 0; i < _client.size(); ++i) {
		if (FD_ISSET(_client[i]->getSocketFd(), &readFdSet) && _client[i]->getState() == READ_REQ){
			read_request(i);
			if (_client[i]->getState() != CLOSE && _client[i]->getRequest()->getState() == PARSE_FINISH)
				FD_SET(_client[i]->getSocketFd(), &writeFdSet);
		}
		if (_client[i]->getState() == CREATE_RESPONSE){
			_client[i]->getResponse()->generate(*_server[0], *_client[i]->getRequest()); /*todo добавить номер сервера*/
			_client[i]->setState(SEND_RESPONSE);
		}
		if (FD_ISSET(_client[i]->getSocketFd(), &writeFdSet) && _client[i]->getState() == SEND_RESPONSE) {
			send_response(i);
			if (_client[i]->getState() == READ_REQ){
				_client[i]->getRequest()->clear();
				_client[i]->getResponse()->clear();
			}
		}
		if (_client[i]->getState() == CLOSE) {
			std::vector<Client *>::iterator it = _client.begin() + (int)i;
			delete _client[i];
			_client.erase(it);
		}
	}
}

void WebServer::send_response(int client_num) {
	_client[client_num]->getSendPos();

	char *buf = new char[_client[client_num]->getResponse()->getResponse().length() + 1];
	strcpy(buf, _client[client_num]->getResponse()->getResponse().c_str());

	size_t len = _client[client_num]->getResponse()->getResponse().length() -_client[client_num]->getSendPos();
	ssize_t s_send = send(_client[client_num]->getSocketFd(), &buf[_client[client_num]->getSendPos()], len, 0);
	if (s_send < 0)
		_client[client_num]->setState(CLOSE);

	std::cout << YELLOW << "Sending a response to the user with ip " << RED << _client[client_num]->getInfoClient()
	<< MAGENTA << ", len = " << s_send
	<< " FD = " << _client[client_num]->getSocketFd() <<  RESET << std::endl;

	_client[client_num]->setSendPos(_client[client_num]->getSendPos() + s_send);
	if (_client[client_num]->getResponse()->getResponse().length() == _client[client_num]->getSendPos()){
		_client[client_num]->setState(READ_REQ);
		_client[client_num]->setSendPos(0);
	}
	if (_client[client_num]->getRequest()->getHead().find("CONNECTION")->second == "close") {
		std::cout << "close connection!!!" << std::endl;
		_client[client_num]->setState(CLOSE);
	}
	delete [] buf;
}

void WebServer::read_request(int client_num) {
	char buffer[BUFSIZE + 1];
	bzero(&buffer, BUFSIZE);
	ssize_t bytes_read;
	bytes_read = recv(_client[client_num]->getSocketFd(), buffer, BUFSIZE, 0);

	if (bytes_read <= 0) {
		_client[client_num]->setState(CLOSE);
		return;
	}
	_client[client_num]->getRequest()->parse(buffer, bytes_read);
	if (_client[client_num]->getRequest()->getState() == PARSE_FINISH){
		std::cout << MAGENTA<< "HttpRequest: Finish parse" << RESET<< std::endl;
		_client[client_num]->setState(CREATE_RESPONSE);
	}
}

void WebServer::initSD(fd_set &readFdSet, fd_set &writeFdSet) {
	FD_ZERO(&readFdSet);
	FD_ZERO(&writeFdSet);

	for (int i = 0; i < _server.size(); ++i) {
		FD_SET(_server[i]->get_sockFd(), &readFdSet);
	}
	for (int i = 0; i < _client.size(); ++i) {
		FD_SET(_client[i]->getSocketFd(), &readFdSet);
		if (_client[i]->getState() != READ_REQ) /*если для клиента есть данные к отправке*/
			FD_SET(_client[i]->getSocketFd(), &writeFdSet);
		if (_client[i]->getSocketFd() > _max_socket_FD)
			_max_socket_FD = _client[i]->getSocketFd();
	}
}

void WebServer::life_cycle() {
	fd_set readFdSet, writeFdSet;
	_max_socket_FD = _server.back()->get_sockFd();

	std::cout << "Waiting on port: " << _server[0]->getPort() << std::endl;
	while (true)
	{
		initSD(readFdSet, writeFdSet); // Инициализизируем структуру сокетов

		select(_max_socket_FD + 1, &readFdSet, &writeFdSet, NULL, NULL); // Ждем пока на сокетах что то не произойдет

		acceptor(readFdSet, writeFdSet); // Принимаем новых клиентов

		handler(readFdSet, writeFdSet); // Обрабатываем запрос

//		std::cout << "DONE!" << std::endl;
	}
}
