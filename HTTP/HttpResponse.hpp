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
	HttpResponse();
	virtual ~HttpResponse() {};
	void generate(Server &server, HttpRequest &request);
private:
	std::string get_loc(Server &server, HttpRequest &request);
	void 		check_method(const std::string& method);

	std::string	_body;
	std::string	_head;
	t_location	_location;
	std::string _loc_name;
	int			_code;
};


#endif //WEBSERVER_HTTPRESPONSE_HPP
