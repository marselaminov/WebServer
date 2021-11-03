//
// Created by lexa on 03.11.2021.
//

#ifndef WEBSERV_PARSER_HPP
#define WEBSERV_PARSER_HPP

#include "Server.hpp"
#include <algorithm>

class Parser {
public:
	Parser(const std::string &file);
	Parser(const Parser &src);
	Parser &operator=(const Parser &src);
	virtual ~Parser();

	const std::vector<Server *> &getServers() const;
	static void	handleServerBlock(std::string &file);

private:
	std::vector<Server *>	servers;
};


#endif //WEBSERV_PARSER_HPP
