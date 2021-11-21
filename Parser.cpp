//
// Created by lexa on 03.11.2021.
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

std::string	get_value(std::string &line, std::string key) {
	std::string temp;
	size_t i = 0;

//	std::cout << "what is it : " << line[i] << std::endl;
	while (line[i] == '\t')
		i++;
	if ((key == "host:" && i != 1) || (key == "port:" && i != 1)
		|| (key == "server_name:" && i != 1) || (key == "error_page:" && i != 1)
		|| (key == "auth_basic_user_file:" && i != 1)
		|| (key == "location:" && i != 2)
		|| (key == "root:" && i != 3) || (key == "autoindex:" && i != 3)
		|| (key == "index:" && i != 3) || (key == "cgi_path:" && i != 3)
		|| (key == "client_max_body_size:" && i != 3) || (key == "access-control-allow-methods:" && i != 3))
		throw std::runtime_error("Tabulation error in config file");
//	if ((line.compare(i, key.size(), key) < 0) || (line.compare(i, key.size(), key) > 0))
//		throw std::runtime_error("Key error in config file");
	i += key.size();
	while (line[i] == '\t' || line[i] == ' ')
		i++;
	temp = line.substr(i, line.size());
//	std::cout << temp << std::endl;
	return (temp);
}

void	Parser::handleLocation(Server *serv, std::vector<std::string> &lines, size_t *i) {
	std::string temp;
	std::map<std::string, t_location> tmpLoc;

//	std::cout << lines.size();
	while (*i < lines.size()) {
		if (lines[*i][0] == '#' || lines[*i].empty() || lines[*i] == "\n")
			*i = *i + 1;
		if (lines[*i].find("location:") != std::string::npos) {
			temp = get_value(lines[*i], "location:");
//			std::cout << temp << std::endl;
			*i = *i + 1;
			t_location location;
			location.autoIndex = false;
			location.client_max_body_size = 0;
			while (*i < lines.size() && lines[*i].find("location:") == std::string::npos) {
				if (lines[*i][0] == '#' || lines[*i].empty() || lines[*i] == "\n") {
					*i = *i + 1;
					continue;
				}
				else if (lines[*i].find("root:") != std::string::npos) {
					std::string root = get_value(lines[*i], "root:");
					location.root = root;
				}
				else if (lines[*i].find("autoindex:") != std::string::npos) {
					std::string autoindex = get_value(lines[*i], "autoindex:");
					if (autoindex == "on")
						location.autoIndex = true;
					else if (autoindex == "off")
						location.autoIndex = false;
					else
						throw std::runtime_error("Autoindex error in the config file");
				}
				else if (lines[*i].find("index:") != std::string::npos) {
					std::string index = get_value(lines[*i], "index:");
					location.index = index;
				}
				else if (lines[*i].find("cgi_path:") != std::string::npos) {
					std::string cgi_path = get_value(lines[*i], "cgi_path:");
					location.cgi_path = cgi_path;
				}
				else if (lines[*i].find("client_max_body_size:") != std::string::npos) {
					std::string client_max_body_size = get_value(lines[*i], "client_max_body_size:");
					try {
						int cast = std::stoi(client_max_body_size);
						if (cast < 0)
							location.client_max_body_size = 0;
						else
							location.client_max_body_size = static_cast<size_t>(cast);
					}
					catch (std::exception &e) {
						throw std::runtime_error("Client_max_body_size error in the config file");
					}
				}
				else if (lines[*i].find("access-control-allow-methods:") != std::string::npos) {
					std::string methods = get_value(lines[*i], "access-control-allow-methods:");

					std::string tmp = methods;
					std::replace(temp.begin(), temp.end(), '\t', ' ');
//					std::cout << tmp << std::endl;
					std::stringstream stream(tmp);

					std::vector<std::string> vector;
					std::string str;

					while (getline(stream, str, ' ')) {
						size_t j = 0;
						while (str[j])
							j++;
						str[j] = '\0';
						vector.push_back(str);
					}

//					for (size_t h = 0; h < vector.size(); ++h)
//						std::cout << vector[h] << std::endl;

					std::vector<std::string> tmpVector;
					size_t idx = 0;
					while (idx < vector.size()) {
						if (!vector[idx].compare("GET"))
							tmpVector.push_back("GET");
						else if (!vector[idx].compare("POST"))
							tmpVector.push_back("POST");
						else if (!vector[idx].compare("PUT"))
							tmpVector.push_back("PUT");
						else if (!vector[idx].compare("DELETE"))
							tmpVector.push_back("DELETE");
						else
							throw std::runtime_error("This method in the config file not allowed");
						++idx;
					}
					if (tmpVector.empty())
						throw std::runtime_error("Where methods, dude?");
//					for (size_t d = 0; d < tmpVector.size(); ++d)
//						location.methods[d] = tmpVector[d];
					location.methods = tmpVector;
//					for (size_t h = 0; h < location.methods.size(); ++h)
//						std::cout << location.methods[h] << std::endl;
				}
				*i = *i + 1;
			}
			tmpLoc.insert(std::make_pair(temp, location));
//			tmpLoc[temp] = location;
		}
		else {
//			std::cout << *i << std::endl;
//			std::cout << lines.size() << std::endl;
			throw std::runtime_error("Where locations, man?");
		}
	}
	serv->setLocation(tmpLoc);
}

void	Parser::handleServerBlock(std::string &file) {
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
//		std::cout << lines[j] << std::endl;
		if (lines[j][0] == '#' || lines[j].empty() || lines[j] == "\n") {
			j++;
			continue;
		}
		if (lines[j].find("host:") != std::string::npos)
			serv->setHost(get_value(lines[j], "host:"));
		else if (lines[j].find("port:") != std::string::npos)
			serv->setPort(get_value(lines[j], "port:"));
		else if (lines[j].find("server_name:") != std::string::npos)
			serv->setServerName(get_value(lines[j], "server_name:"));
		else if (lines[j].find("auth_basic_user_file:") != std::string::npos)
			serv->setAuthBasicUserFile(get_value(lines[j], "auth_basic_user_file:"));
		else if (lines[j].find("error_page:") != std::string::npos)
			serv->setErrorPage(get_value(lines[j], "error_page:"));
		else if (lines[j].find("location:") != std::string::npos) {
			handleLocation(serv, lines, &j);
			break;
		}
		else
			throw std::runtime_error("Error in the config file");
		j++;
	}
//	std::cout << j << std::endl;
//	std::cout << lines.size() << std::endl;
	if (j != lines.size())
		throw std::runtime_error("Some error in here, ours parser is crap");
	this->servers.push_back(serv);
}

void	Parser::work_with_file(const std::string &file) {
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
	input.close();
}

Parser::Parser(const std::string &file) {
	work_with_file(file);
}