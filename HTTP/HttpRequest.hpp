//
// Created by Maya Queen on 10/27/21.
//

#ifndef WEBSERV_HTTPREQUEST_HPP
#define WEBSERV_HTTPREQUEST_HPP

#include <iostream>
#include <map>
#include <vector>
#include "../ChunkedRequest.hpp"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

#define CRLF "\r\n"
#define BODY_SEP "\r\n\r\n" // 2 строки

class HttpRequest {
public:
	void parse(char *buf);
	void parseHead();
	void parseBody();
	void handleChunk(size_t startIndex);
	void parseQueryString();
	std::string getContentType();

	std::string get_path();
	std::string get_method();
private:
	std::string _strBuf;
	std::string _method;
	std::string _path;
	std::string _parameters; // query string
	std::vector<ChunkedRequest *> _chunk;
public:
	const std::string &getParameters() const;

private:
	std::map<std::string, std::string>	_head;
public:
	const std::map<std::string, std::string> &getHead() const;
};

#endif //WEBSERV_HTTPREQUEST_HPP
