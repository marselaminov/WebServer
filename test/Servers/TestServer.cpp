//
// Created by Maya Queen on 10/21/21.
//

#include "TestServer.hpp"

TestServer::TestServer() : Server(AF_INET, SOCK_STREAM, 0, 5555, INADDR_ANY, 10){
	launch();
}

void TestServer::_acceptor() {
	struct sockaddr_in address = get_socket()->get_address();
	int addrlen = sizeof (address);
	_new_socket = accept(get_socket()->get_sock_fd(),
					(struct sockaddr *)&address, (socklen_t *)&addrlen);
	if (_new_socket < 0)
		throw (std::runtime_error("TestServer: acceptor"));
	read(_new_socket, _buf, 30000);
}

void TestServer::_handler() {
	std::cout << _buf << std::endl;
	std::cout << "=================================" << std::endl;
}

void TestServer::_responder() {
	std::string hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 13\n\nMarsel chort!";
	write(_new_socket , hello.c_str() , hello.size());
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
