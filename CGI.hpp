//
// Created by Legate Gunship on 11/15/21.
//

#ifndef WEBSERVER_CGI_HPP
#define WEBSERVER_CGI_HPP

#include "../HTTP/HttpRequest.hpp"
#include "../HTTP/HttpResponse.hpp"
#include "Server.hpp"
#include <unistd.h>

class HttpRequest;

class HttpResponse;

class CGI {
public:
	CGI(Server *server, HttpRequest *request, std::string cgiPath);
	virtual ~CGI();
	void exec();
	void handleBody();

private:
	char **_env;
	std::string _cgiPath;
	HttpRequest *_request;
	long _bodySize;
	size_t _bodySizeForReturn;
public:
	size_t getBodySizeForReturn() const;

private:
	std::string _body;
public:
	const std::string &getBody() const;

private:
	int _code;
public:
	int getCode() const;
};

#endif //WEBSERVER_CGI_HPP
