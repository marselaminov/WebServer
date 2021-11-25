//
// Created by lexa on 02.11.2021.
//

#ifndef WEBSERVER_WEBSERVER_HPP
#define WEBSERVER_WEBSERVER_HPP

#include "Server.hpp"
#include "Client.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Parser.hpp"

# define RED     "\x1b[31m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

class HttpResponse;

class HttpRequest;

class Client;

class WebServer {
public:
	WebServer(const char *file);

	virtual ~WebServer();

	void start();

	void life_cycle();

private:
	std::vector<Server *> _server;
	std::vector<Client *> _client;
	int _max_socket_FD;


	void initSD(fd_set &readFdSet, fd_set &writeFdSet);

	void acceptor(fd_set &readFdSet);

	void handler(fd_set &readFdSet, fd_set &writeFdSet);

	void read_request(int client_num);

	void send_response(int client_num);
};


#endif //WEBSERVER_WEBSERVER_HPP
