//
// Created by Legate Gunship on 11/15/21.
//

#ifndef WEBSERVER_CGI_HPP
#define WEBSERVER_CGI_HPP

#include "../HTTP/HttpRequest.hpp"
#include "../HTTP/HttpResponse.hpp"
#include "Server.hpp"

class HttpRequest;

class HttpResponse;

class CGI {
public:
	CGI(Server *server, HttpRequest *request, HttpResponse *response, char *cgiPath);

	virtual ~CGI();

	void exec();


private:
	char **_env;
	char *_cgiPath;
	HttpResponse *_response;
	HttpRequest *_request;
	long _bodySize;
};

#endif //WEBSERVER_CGI_HPP
