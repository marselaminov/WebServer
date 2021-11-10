//
// Created by Legate Gunship on 11/10/21.
//

#ifndef WEBSERVER_CLIENT_HPP
#define WEBSERVER_CLIENT_HPP

#include <iostream>
#include <arpa/inet.h>
#include "../HTTP/HttpResponse.hpp"
#include "../HTTP/HttpRequest.hpp"

# define MAGENTA "\x1b[35m"
# define RESET   "\x1b[0m"

class HttpResponse;
class HttpRequest;

class Client {
public:
	Client(const sockaddr_in &addr, unsigned int port, const std::string &host, int socketFd);
	virtual ~Client();

	HttpRequest *getRequest() const;
	HttpResponse *getResponse() const;

	unsigned int getPort() const;

	char *getInfoClient() const;

	const std::string &getHost() const;

	int getSocketFd() const;

private:
	HttpRequest			*request;
	HttpResponse		*response;
	struct sockaddr_in	addr;
	unsigned int		port;
	std::string			host;
	char				*infoClient;
	int					socketFd;
};

#endif //WEBSERVER_CLIENT_HPP
