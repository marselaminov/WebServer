//
// Created by lexa on 01.11.2021.
//

#ifndef WEBSERVER_HTTPRESPONSE_HPP
#define WEBSERVER_HTTPRESPONSE_HPP

class WebServer;
#include <iostream>

#include "../WebServer.hpp"

class HttpResponse {
public:
	~HttpResponse() {};
	void generate(Server &server, HttpRequest &request);
private:
	t_location get_loc(Server &server, HttpRequest &request);

	std::string _body;
	std::string _head;
	int			_code;
};


#endif //WEBSERVER_HTTPRESPONSE_HPP
