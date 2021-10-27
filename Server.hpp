//
// Created by Legate Gunship on 10/27/21.
//

#ifndef WEBSERV_SERVER_HPP
#define WEBSERV_SERVER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <netinet/in.h>

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
	Server(const Server &src);
	Server &operator=(const Server &src);
	virtual ~Server();

	const sockaddr_in &getSockAddr() const;

	void setSockAddr(const sockaddr_in &sockAddr);

	const std::map<std::string, t_location> &getLocation() const;

	void setLocation(const std::map<std::string, t_location> &location);

	const std::string &getServerName() const;

	void setServerName(const std::string &serverName);

	const std::string &getHost() const;

	void setHost(const std::string &host);

	const std::string &getRoot() const;

	void setRoot(const std::string &root);

	const std::string &getErrorPage() const;

	void setErrorPage(const std::string &errorPage);

	unsigned int getPort() const;

	void setPort(unsigned int port);

	unsigned int getClientMaxBodySize() const;

	void setClientMaxBodySize(unsigned int clientMaxBodySize);

	int getErrorPageCode() const;

	void setErrorPageCode(int errorPageCode);

	int getSocketFd() const;

	int	createSocket();


private:
	struct sockaddr_in					sockAddr;
	std::map<std::string, t_location>	location;
	std::string							serverName;
	std::string 						host;
	std::string 						root;
	std::string 						errorPage;
	unsigned int						port;
	unsigned int						client_max_body_size;
	int 								errorPageCode;
	int									socketFd;
};


#endif //WEBSERV_SERVER_HPP
