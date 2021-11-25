//
// Created by Legate Gunship on 11/10/21.
//

#ifndef WEBSERVER_CLIENT_HPP
#define WEBSERVER_CLIENT_HPP

#include <iostream>
#include <arpa/inet.h>
#include "HttpResponse.hpp"
#include "HttpRequest.hpp"

#define BUFSIZE 555555

class HttpResponse;

enum States {
	READ_REQ,
	CREATE_RESPONSE,
	SEND_RESPONSE,
	CLOSE
};

class Client {
public:
	Client(const sockaddr_in &addr, unsigned int port, const std::string &host, int socketFd);

	virtual ~Client();

	HttpRequest *getRequest();

	unsigned int getPort() const;

	HttpResponse *getResponse();

	char *getInfoClient() const;

	const std::string &getHost() const;

	int getSocketFd() const;

	States getState();

	ssize_t getSendPos() const;

	void setState(States state);

	void setSendPos(ssize_t pos);


private:
	HttpRequest *request;
	HttpResponse *response;
	struct sockaddr_in addr;
	unsigned int port;
	std::string host;
	char *infoClient;
	int socketFd;
	States _state;
	ssize_t _send_pos;
};

#endif //WEBSERVER_CLIENT_HPP
