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


void WebServer::_acceptor() {
	struct sockaddr_in address = _server[0]->get_sockAddr();
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
	std::stringstream response_body;
	std::stringstream response;
	_response = new HttpResponse;
	_response->generate(*_server[0], *_request);

	response_body << "<link rel=\"icon\" href=\"data:,\">\n"
				  << "<title>Test C++ HTTP Server</title>\n"
				  << "<h1>Test page</h1>\n"
				  << "<p>This is body of the test page...</p>\n"
				  << "<h2>Request headers</h2>\n"
				  << "<pre>" << _buf << "</pre>\n"
				  << "<em><small>Test C++ Http Server</small></em>\n";

	// Формируем весь ответ вместе с заголовками
	response << "HTTP/1.1 200 OK\r\n"
			 << "Version: HTTP/1.1\r\n"
			 << "Content-Type: text/html; charset=utf-8\r\n"
			 << "Content-Length: " << response_body.str().length()
			 << "\r\n\r\n"
			 << response_body.str();

//	std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nMarsel chort!";
	write(_new_socket , response.str().c_str() , response.str().size());
	close(_new_socket);
	delete _response;
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
