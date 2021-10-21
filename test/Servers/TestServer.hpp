//
// Created by Maya Queen on 10/21/21.
//

#ifndef WEBSERV_TESTSERVER_HPP
#define WEBSERV_TESTSERVER_HPP

#include "Server.hpp"

class TestServer : public Server{
public:
	TestServer();
	~TestServer() {};
	void launch();

private:
	char _buf[3000];
	int _new_socket;

	void _acceptor();
	void _handler();
	void _responder();
};


#endif //WEBSERV_TESTSERVER_HPP
