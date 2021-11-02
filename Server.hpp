//
// Created by Legate Gunship on 10/27/21.
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
#include <netinet/in.h>

typedef struct	s_location {
    std::vector<std::string>	methods;
    std::string					index;
    std::string					root;
	std::string					url;
	std::string					cgi_path;
	size_t						client_max_body_size;
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

	const std::string &getErrorPage() const;

	void setErrorPage(const std::string &errorPage);

	unsigned int getPort() const;
	void setPort(const std::string &port);

	int getErrorPageCode() const;
	void setErrorPageCode(int errorPageCode);

	int getSocketFd() const;
	int	createSocket();

	const std::string &getAuthBasicUserFile() const;
	void setAuthBasicUserFile(const std::string &authBasicUserFile);

private:
	struct sockaddr_in					sockAddr;
	int									socketFd;
	std::string 						host;
	unsigned int						port;
	std::string							serverName;
	std::string							auth_basic_user_file;
	std::string 						errorPage;
	std::map<std::string, t_location>	location;
	int 								errorPageCode;
};


#endif //WEBSERV_SERVER_HPP
