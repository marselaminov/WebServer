//
// Created by Legate Gunship on 11/10/21.
//

#ifndef WEBSERVER_CLIENT_HPP
#define WEBSERVER_CLIENT_HPP

#include <iostream>
#include <arpa/inet.h>
#include "../HTTP/HttpResponse.hpp"
#include "../HTTP/HttpRequest.hpp"

//#define _Client___Ready_To_Read 1
//#define _Client___Ready_To_Parse 2
//#define _Client___Ready_To_Respond 3
//#define _Client___Ready_To_Send 4
//#define _Client___Ready_To_Close 5

#define BUFSIZE 555555

class HttpResponse;
class HttpRequest;

enum States
		{
			READ_REQ,
			CREATE_RESPONSE,
			SEND_RESPONSE,
			CLOSE
		};

class Client {
public:
	Client(const sockaddr_in &addr, unsigned int port, const std::string &host, int socketFd);
	virtual ~Client();

	/* GETTERS */
	HttpRequest		*getRequest();
	unsigned int	getPort() const;
	HttpResponse	*getResponse();
	char			*getInfoClient() const;
	const			std::string &getHost() const;
	int				getSocketFd() const;
//	int				getFlag() const;
	States			getState();
	ssize_t			getSendPos();

	/* SETTERS */
//	void setFlag(int flag);
	void setRequest(HttpRequest *request);
	void setResponse(HttpResponse *response);
	void setState(States state);
	void setSendPos(ssize_t pos);


private:
	HttpRequest			*request;
	HttpResponse		*response;
	struct sockaddr_in	addr;
	unsigned int		port;
	std::string			host;
	char				*infoClient;
	int					socketFd;
//	int 				_flag;
	States				_state;
	ssize_t				_send_pos;
};

#endif //WEBSERVER_CLIENT_HPP
