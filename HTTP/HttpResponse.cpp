//
// Created by lexa on 01.11.2021.
//

#include "HttpResponse.hpp"

void HttpResponse::generate(Server &server, HttpRequest &request) {
	_code = 200;
	std::string index = get_loc(server, request);
	check_method(request.get_method());

	std::string merged_Path = _location.root;
	if (merged_Path[merged_Path.length() - 1] != '/')
		merged_Path += '/';
	if (!index.empty())
		index.erase(0, 1);
	merged_Path += index;
	std::cout << "Merged path: " << merged_Path << std::endl;
	struct stat fileInfo;
	if (_code < 400){
		if (stat(merged_Path.c_str(), &fileInfo) == -1)
			_code = 404;

	}
	std::cout << "Code: " << _code << std::endl;
}

void HttpResponse::check_method(const std::string& method) {
	for (std::vector<std::string>::iterator it = _location.methods.begin(); it !=_location.methods.end(); ++it)
		if (method == *it)
			return;
	_code = 405;
}

std::string HttpResponse::get_loc(Server &server, HttpRequest &request) {
	std::string path = request.get_path();
	std::string index;

	if (path.size() != 1 && path[path.size() - 1] == '/') {
		index += '/';
		path.erase(path.size() - 1, 1);
	}
	while (true){
		for (std::map<std::string, t_location>::const_iterator it = server.getLocation().begin(); it !=  server.getLocation().end(); ++it) {
			if (it->first == path) {
				_location = it->second;
				_loc_name = it->first;
				return index;
			}
			if (path == "/"){
				_code = 404;
				return index;
			}
		}
		std::string tmp = std::string(path, path.rfind('/'));
		index.insert(0, tmp);
		path.erase(path.rfind('/'));
		if (path.size() == 0){
			path += "/";
		}
	}
}