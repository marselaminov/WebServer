//
// Created by lexa on 01.11.2021.
//

#include "HttpResponse.hpp"

void HttpResponse::generate(Server &server, HttpRequest &request) {
	_code = 200;
	int error_flag = 0;

	try {
		init(server, request);					//поиск location, обработка ошибок, проверка файла
	}
	catch (std::exception &e) {
		error_flag = 1;
		std::cout << "Code: " << _code << std::endl;
	}
}

void HttpResponse::init(Server &server, HttpRequest &request) {
	std::string index = get_loc(server, request);	//поиск подходящего location
	check_method(request.get_method());				//проверка на разрешенные методы
	if (_code >= 400)
		throw std::exception();

	std::string merged_Path = _location.root;				//merged_Path - путь по которому будет искаться запрашиваемый файл
	if (merged_Path[merged_Path.length() - 1] != '/')
		merged_Path += '/';
	if (!index.empty())
		index.erase(0, 1);
	merged_Path += index;

	struct stat fileInfo;									//информация о файле или диреткории по пути merged_Path
	if (stat(merged_Path.c_str(), &fileInfo) == -1) {
		_code = 404;
		throw std::exception();
	}

	if (S_ISDIR(fileInfo.st_mode))						//если merged_Path папка
		check_dir(request, &fileInfo, merged_Path);

	std::cout << "Merged path: " << merged_Path << std::endl;
}

void
HttpResponse::check_dir(HttpRequest &request, struct stat *fileInfo, std::string &path) {
	if (!_location.autoIndex && _location.index.empty()){
		if (!_location.autoIndex)
			_code = 403;
		else
			_code = 404;
		throw std::exception();
	}
	if (!_location.autoIndex && !_location.index.empty()){
		if (path[path.length() - 1] != '/')
			path += '/';
		path += _location.index;
		int fd = open(path.c_str(), O_RDONLY);
		if (fd < 0){
			_code = 404;
			close(fd);
			throw std::exception();
		}
		close(fd);
		stat(path.c_str(), fileInfo);
	}
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