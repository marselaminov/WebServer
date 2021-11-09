//
// Created by Maya Queen on 10/27/21.
//

#ifndef WEBSERV_HTTPREQUEST_HPP
#define WEBSERV_HTTPREQUEST_HPP

#include <iostream>
#include <map>

#define CRLF "\r\n"
#define BODY_SEP "\r\n\r\n"

class HttpRequest {
public:
	void parse(char *buf);
	void parseHead();
	void parseQueryString();

	std::string get_path();
	std::string get_method();
private:
	std::string 						_strBuf;
	std::string 						_method;
	std::string 						_path;
	std::string							_parameters;
	std::map<std::string, std::string>	_head;
};


#endif //WEBSERV_HTTPREQUEST_HPP
