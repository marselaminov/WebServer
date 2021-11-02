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

#define BACKLOG 1024

typedef struct	s_location {
	std::vector<std::string>	methods;
	std::vector<std::string>	index;
	std::string					root;
	std::string					url;
	std::string					cgi_path;
	bool						autoIndex;
}				t_location;

class Server {
public:
	Server();
	virtual ~Server() {};

	void	createSocket();

	sockaddr_in get_sockAddr();
	int get_sockFd();
private:
	struct sockaddr_in					_sockAddr;
	std::map<std::string, t_location>	_location;
	std::string							_serverName;
	std::string 						_host;
	std::string 						_root;
//	std::string 						_errorPage;
	unsigned int						_port;
//	unsigned int						_client_max_body_size;
//	int 								_errorPageCode;
	int									_socketFd;
};


#endif