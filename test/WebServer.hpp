//
// Created by lexa on 02.11.2021.
//

#ifndef WEBSERVER_WEBSERVER_HPP
#define WEBSERVER_WEBSERVER_HPP

#include <iostream>
#include <vector>
#include "Server.hpp"
#include "HTTP/HttpRequest.hpp"
#include "HTTP/HttpResponse.hpp"
#include "Parser.hpp"

class WebServer {
public:
	WebServer();
	~WebServer() {};

	void start();
	void life_cycle();
private:
	std::vector<Server *>	_server;
	int						_new_socket;
	char					_buf[3000];
	HttpRequest				*_request;

	void _acceptor();
	void _handler();
	void _responder();
};


#endif //WEBSERVER_WEBSERVER_HPP
