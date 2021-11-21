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
	void	work_with_file(const std::string &file);
	void	handleServerBlock(std::string &file, size_t i);
	void	handleLocation(Server *serv, std::vector<std::string> &lines, size_t *i, size_t servIdx);

private:
	std::vector<Server *>	servers;
};


#endif //WEBSERV_PARSER_HPP
