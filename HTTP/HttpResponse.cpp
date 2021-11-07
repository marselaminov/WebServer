//
// Created by lexa on 01.11.2021.
//

#include "HttpResponse.hpp"

void HttpResponse::generate(Server &server, HttpRequest &request) {
	t_location my_loc;
	my_loc = get_loc(server, request);

}

t_location HttpResponse::get_loc(Server &server, HttpRequest &request) {
	std::string path = request.get_path();
	std::string index;

	if (path.size() != 1 && path[path.size() - 1] == '/') {
		index += '/';
		path.erase(path.size() - 1, 1);
	}
	while (true){
		for (std::map<std::string, t_location>::const_iterator it = server.getLocation().begin(); it !=  server.getLocation().end(); ++it) {
			std::cout << "loc: " << it->first << " ====== path: " << path << std::endl;
			if (it->first == path) {
				std::cout << "FIND" << std::endl;
				break;
			}
		}
		std::string tmp = std::string(path, path.rfind('/'));
		index.insert(0, tmp);
		path.erase(path.rfind('/'));
		if (path.size() == 0){
			path += "/";
		}
		std::cout << "path: " << path << std::endl;
		std::cout << "index: " << index << std::endl;
	}
//	std::cout << "path: " << path << std::endl;
//	std::cout << "index: " << index << std::endl;
	t_location tmp;
	return tmp;
}