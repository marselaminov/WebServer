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


void WebServer::_acceptor() {
	struct sockaddr_in address = _server[0]->getSockAddr();
	int addrlen = sizeof (address);
	_new_socket = accept(_server[0]->get_sockFd(), (struct sockaddr *)&address, (socklen_t *)&addrlen);
	if (_new_socket < 0)
		throw (std::runtime_error("WebServer: acceptor"));
	read(_new_socket, _buf, 30000);
}

void WebServer::_handler() {
//	std::cout << _buf << std::endl;
	_request = new HttpRequest;
	_request->parse(_buf);
	std::cout << "=================================" << std::endl;
}

void WebServer::_responder() {
	_response = new HttpResponse;
	_response->generate(*_server[0], *_request);

	write(_new_socket , _response->getResponse().c_str() , _response->getResponse().size());
	close(_new_socket);
	delete _response;
	delete _request;
}

void WebServer::life_cycle() {
	while (true)
	{
		std::cout << "Waiting on port: " << _server[0]->getPort() << std::endl;
		_acceptor();
		_handler();
		_responder();
		std::cout << "DONE!" << std::endl;
	}
}
