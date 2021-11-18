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

enum RequestStates {
	PARSE_QUERY_STR,
	PARSE_HEAD,
	PARSE_BODY,
	PARSE_FINISH
};

class HttpRequest {
public:
	HttpRequest();

	void parse(char *buf, size_t bytes_read);
	void clear();

	std::string get_path();
	std::string get_method();
	const std::string &getParameters() const;
	const std::map<std::string, std::string> &getHead() const;
	RequestStates	getState();

private:
	std::string							_strBuf;
	std::string							_method;
	std::string							_path;
	std::string							_parameters; // query string
	std::vector<ChunkedRequest *>		_chunk;
	std::map<std::string, std::string>	_head;
	RequestStates						_state;

	void parseHead();
	void parseBody();
	void handleChunk(size_t startIndex);
	void parseQueryString();
	void handleContentBody();
};

#endif //WEBSERV_HTTPREQUEST_HPP
