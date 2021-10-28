//
// Created by Legate Gunship on 10/27/21.
//

#ifndef WEBSERV_PARSER_HPP
#define WEBSERV_PARSER_HPP

#include "Server.hpp"

class Parser {
public:
	Parser(const std::string &file);
	Parser(const Parser &src);
	Parser &operator=(const Parser &src);
	virtual ~Parser();

	const std::vector<Server *> &getServers() const;

private:
	std::vector<Server *>	servers;
};


#endif //WEBSERV_PARSER_HPP
