//
// Created by Maya Queen on 10/21/21.
//

#include "TestServer.hpp"
#include <sstream>

TestServer::TestServer() : Server(AF_INET, SOCK_STREAM, 0, 5555, INADDR_ANY, 10){
	launch();
}

void TestServer::_acceptor() {
	struct sockaddr_in address = get_socket()->get_address();
	int addrlen = sizeof (address);
	std::cout << "FD: " << get_socket()->get_sock_fd() << "\n"
			  << "addrlen: " << addrlen << "\n"
			  << "addres.port: " << address.sin_port << "\n";
	_new_socket = accept(get_socket()->get_sock_fd(),
					(struct sockaddr *)&address, (socklen_t *)&addrlen);
	if (_new_socket < 0)
		throw (std::runtime_error("TestServer: acceptor"));
	read(_new_socket, _buf, 30000);
}

void TestServer::_handler() {
	std::cout << _buf << std::endl;
	_request = new HttpRequest;
	_request->parse(_buf);
	std::cout << "=================================" << std::endl;
}

void TestServer::_responder() {
	std::stringstream response_body;
	std::stringstream response;
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
}

void TestServer::launch() {
	while (true)
	{
		std::cout << "Waiting..." << std::endl;
		_acceptor();
		_handler();
		_responder();
		std::cout << "DONE!" << std::endl;
	}
}
