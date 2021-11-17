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

#define _Client___Ready_To_Read 1
#define _Client___Ready_To_Parse 2
#define _Client___Ready_To_Respond 3
#define _Client___Ready_To_Send 4
#define _Client___Ready_To_Close 5

class HttpResponse;
class HttpRequest;

class Client {
public:
	Client(const sockaddr_in &addr, unsigned int port, const std::string &host, int socketFd);
	virtual ~Client();

	HttpRequest *getRequest();
	HttpResponse *getResponse();

	unsigned int getPort() const;

	char *getInfoClient() const;

	const std::string &getHost() const;

	int getSocketFd() const;

	int getFlag() const;
	void setFlag(int flag);
private:
	HttpRequest			*request;
public:
	void setRequest(HttpRequest *request);

	void setResponse(HttpResponse *response);

private:
	HttpResponse		*response;
	struct sockaddr_in	addr;
	unsigned int		port;
	std::string			host;
	char				*infoClient;
	int					socketFd;
	int 				_flag;
};

#endif //WEBSERVER_CLIENT_HPP
