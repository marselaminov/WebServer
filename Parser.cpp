//
// Created by Legate Gunship on 10/27/21.
//

#include "Parser.hpp"

const std::vector<Server *> &Parser::getServers() const {
	return servers;
}

Parser::Parser(const Parser &src) {(void)src;}

Parser & Parser::operator=(const Parser &src) {
	(void)src;
	return (*this);
}

Parser::~Parser() {}

std::string	get_value()

void	handleServerBlock(std::string &file) {
//	std::cout << file;
	std::vector<std::string> lines;
	std::stringstream stream(file);
	std::string temp;

	while (getline(stream, temp, '\n')) {
		size_t i = 0;
		while (temp[i])
			i++;
		temp[i] = '\0';
		lines.push_back(temp);
	}
//	size_t j = 0;
//	while (j < lines.size()) {
//		std::cout << lines[j] << std::endl;
//		j++;
//	}
	//---------------------------------------------
	size_t j = 1;
	Server *serv = new Server();
	while (j < lines.size()) {
		if (lines[j].find("host") != std::string::npos)
			serv->setHost("ccc");
		else if (lines[j][0] == '#' || lines[j].empty() || lines[j] == "\n") {
			j++;
			continue;
		}
		j++;
	}
	if (j != lines.size())
		throw std::runtime_error("Some error in here, ours parser is crap");
}

void	work_with_file(const std::string &file) {
	std::ifstream input;
	input.open(file);
	if (!input.is_open())
		throw std::runtime_error("File corrupted");
	//------------------------------------------
	std::string	str;
	std::stringstream stream;

	while (getline(input, str)) {
		stream << str << std::endl;
	}
	if (stream.str().empty()) {
		throw std::runtime_error("Where is data on file, dude?");
	}
	//std::cout << stream.str();
	if (stream.str().find("server:") != std::string::npos) {
		std::string all(stream.str());
		handleServerBlock(all);
	}
}

Parser::Parser(const std::string &file) {
	work_with_file(file);

}
