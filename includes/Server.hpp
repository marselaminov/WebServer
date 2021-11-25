//
// Created by lexa on 02.11.2021.
//
#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include <strings.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define BACKLOG 1024

typedef struct s_location {
	std::vector<std::string> methods;
	std::string index;
	std::string root;
	std::string cgi_path;
	size_t client_max_body_size;
	bool autoIndex;
} t_location;

class Server {
public:
	Server();

	virtual ~Server() {};

	void createSocket();

	int get_sockFd() const;

	const std::map<std::string, t_location> &getLocation() const;

	void setLocation(const std::map<std::string, t_location> &location);

	void setServerName(const std::string &serverName);

	void setHost(const std::string &host);

	const std::string &getErrorPage() const;

	void setErrorPage(const std::string &errorPage);

	unsigned int getPort() const;

	void setPort(const std::string &port);

	int getErrorPageCode() const;


	std::string getHost() const;


private:
	std::map<std::string, t_location> _location;
	std::string _serverName;
public:
	const std::string &getServerName() const;


private:
	std::string _host;


private:
	std::string _errorPage;
	unsigned int _port;
	int _errorPageCode;
	int _socketFd;
};


#endif