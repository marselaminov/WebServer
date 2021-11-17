//
// Created by lexa on 02.11.2021.
//

#include "WebServer.hpp"

WebServer::WebServer() {
	Parser *parser;

	try {
		parser = new Parser("../test1.conf");
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


void WebServer::_acceptor(fd_set &readFdSet, fd_set &writeFdSet) {

	for (size_t i = 0; i < _server.size(); ++i) {
		if (FD_ISSET(_server[i]->get_sockFd(), &readFdSet)){
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
			if (_client.back()->getSocketFd() > _max_socket_FD)
				_max_socket_FD = _client.back()->getSocketFd();
		}
	}
}

void WebServer::_handler(fd_set &readFdSet, fd_set &writeFdSet) {
	for (int i = 0; i < _client.size(); ++i) {
		if (FD_ISSET(_client[i]->getSocketFd(), &readFdSet)) {
			ssize_t bytes_read;
			bytes_read = recv(_client[i]->getSocketFd(), _buf, 3000, 0);
			_client[i]->setFlag(_Client___Ready_To_Parse);
			if (bytes_read <= 0) {
				std::cout << "read: " << _client[i]->getFlag() <<  std::endl;
				_client[i]->setFlag(_Client___Ready_To_Read);
			}
		}
		if (_client[i]->getFlag() == _Client___Ready_To_Parse) {
			_client[i]->getRequest()->parse(_buf);
			_client[i]->setFlag(_Client___Ready_To_Respond);
		}
		if (_client[i]->getFlag() == _Client___Ready_To_Respond)
		{
			_client[i]->getResponse()->generate(*_server[0], *_client[i]->getRequest());
			_client[i]->setFlag(_Client___Ready_To_Send);
		}
		if (_client[i]->getFlag() == _Client___Ready_To_Send)
		{
			ssize_t s_send = send(_client[i]->getSocketFd(), _client[i]->getResponse()->getResponse().c_str(),
								  _client[i]->getResponse()->getResponse().size() , 0);
//			if (s_send < 0){
				_client[i]->setFlag(_Client___Ready_To_Read);
//			}
		}
		std::cout << "=================================" << std::endl;
	}
}

//void WebServer::_responder() {
//	_response = new HttpResponse;
//	_response->generate(*_server[0], *_request);
//
//	write(_new_socket , _response->getResponse().c_str() , _response->getResponse().size());
//	close(_new_socket);
//	delete _response;
//	delete _request;
//}

void WebServer::initSD(fd_set &readFdSet, fd_set &writeFdSet) {
	FD_ZERO(&readFdSet);
	FD_ZERO(&writeFdSet);

	for (int i = 0; i < _server.size(); ++i) {
		FD_SET(_server[i]->get_sockFd(), &readFdSet);
	}
	for (int i = 0; i < _client.size(); ++i) {
		FD_SET(_client[i]->getSocketFd(), &readFdSet);
		if (_client[i]->getFlag() != _Client___Ready_To_Read)/*если y клиента есть данные*/
			FD_SET(_client[i]->getSocketFd(), &writeFdSet);
		if (_client[i]->getSocketFd() > _max_socket_FD)
			_max_socket_FD = _client[i]->getSocketFd();
	}
}

void WebServer::life_cycle() {
	fd_set readFdSet, writeFdSet;
	_max_socket_FD = _server.back()->get_sockFd();

	while (true)
	{
		std::cout << "Waiting on port: " << _server[0]->getPort() << std::endl;
		initSD(readFdSet, writeFdSet);

		select(_max_socket_FD + 1, &readFdSet, &writeFdSet, NULL, NULL);

		_acceptor(readFdSet, writeFdSet);

		_handler(readFdSet, writeFdSet);

//		_responder();

		std::cout << "DONE!" << std::endl;
	}
}
