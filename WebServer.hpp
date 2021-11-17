//
// Created by lexa on 02.11.2021.
//

#ifndef WEBSERVER_WEBSERVER_HPP
#define WEBSERVER_WEBSERVER_HPP

#include <iostream>

#include <vector>
#include "Server.hpp"
#include "Client.hpp"
#include "HTTP/HttpRequest.hpp"
#include "HTTP/HttpResponse.hpp"
#include "Parser.hpp"
# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"
#define PORT   8888

class HttpResponse;
class Client;

class WebServer {
public:
	WebServer();
	virtual ~WebServer() {};

	void start();
	void life_cycle();
private:
	std::vector<Server *>	_server;
	std::vector<Client *>	_client;
	int						_new_socket;
	int 					_max_socket_FD;
	char					_buf[3000];
//	HttpRequest				*_request;
	HttpResponse			*_response;

	int _flag;

	void initSD(fd_set &readFdSet, fd_set &writeFdSet);
	void _acceptor(fd_set &readFdSet, fd_set &writeFdSet);
	void _handler(fd_set &readFdSet, fd_set &writeFdSet);
//	void _responder();
};


#endif //WEBSERVER_WEBSERVER_HPP
