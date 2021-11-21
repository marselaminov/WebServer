//
// Created by lexa on 02.11.2021.
//
#ifndef WEBSERV_SERVER_HPP
#define WEBSERV_SERVER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <map>
#include <strings.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define BACKLOG 200

typedef struct	s_location {
	std::vector<std::string>	methods;
	std::string					index;
	std::string					root;
	std::string					cgi_path;
	size_t						client_max_body_size;
	bool						autoIndex;
}				t_location;

class Server {
public:
	Server();
	virtual ~Server() {};

	void	createSocket();

	int get_sockFd();

	const std::map<std::string, t_location> &getLocation() const;

	void setLocation(const std::map<std::string, t_location> &location);

	void setServerName(const std::string &serverName);

	void setHost(const std::string &host);

	const std::string &getErrorPage() const;

	void setErrorPage(const std::string &errorPage);

	unsigned int getPort() const;
	void setPort(const std::string &port);

	int getErrorPageCode() const;

	void setAuthBasicUserFile(const std::string &authBasicUserFile);

	std::string getHost() const;

private:
	struct sockaddr_in					_sockAddr;
public:
	const sockaddr_in &getSockAddr() const;

private:
	std::map<std::string, t_location>	_location;
	std::string							_serverName;
public:
	const std::string &getServerName() const;


private:
	std::string 						_host;
public:
//	std::string &getHost() const;

private:
	std::string 						_errorPage;
	unsigned int						_port;
	int 								_errorPageCode;
	int									_socketFd;
	std::string							_auth_basic_user_file;
};


#endif