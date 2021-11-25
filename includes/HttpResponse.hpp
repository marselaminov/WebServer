//
// Created by lexa on 01.11.2021.
//

#ifndef WEBSERVER_HTTPRESPONSE_HPP
#define WEBSERVER_HTTPRESPONSE_HPP

#include <iostream>
#include "WebServer.hpp"
#include "CGI.hpp"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

class Client;

class HttpRequest;

class WebServer;

class HttpResponse {
public:
	~HttpResponse() {};

	HttpResponse();

	void generate(Server &server, HttpRequest &request);

	std::string getResponse();

	void clear();

private:
	std::string get_loc(Server &server, HttpRequest &request);

	void check_method(const std::string &method);

	void init(Server &server, HttpRequest &request);

	void check_dir(HttpRequest &request);

	void GET_request();

	void POST_request(HttpRequest &request, Server &server);

	void DELETE_request();

	void PUT_request(HttpRequest &request);

	void error_body(Server &server);

	void standart_error_body();

	void setStatusMessages();

	std::string getStatusMessages(int &code);

	void create_header();

private:
	std::string _head;
	t_location _location;
	std::string _loc_name;
	int _code;
	std::string _to_send;
	std::string _body;

private:
	// после отработки в CGI
	struct stat _fileInfo;
	std::string _merged_path;
	std::map<int, std::string> _status_messages;
};

std::string get_autoindex(std::string &path, std::string &root);

#endif //WEBSERVER_HTTPRESPONSE_HPP
