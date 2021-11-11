//
// Created by lexa on 01.11.2021.
//

#include "HttpResponse.hpp"

void HttpResponse::generate(Server &server, HttpRequest &request) {
	_code = 200;
	int error_flag = 0;

	try {
		init(server,request);                    //поиск location, обработка ошибок, проверка файла
	}
	catch (std::exception &e) {
		error_flag = 1;
		std::cerr << "ERROR: " << _code << std::endl;
	}
	if (!error_flag) {
		try {
			if (request.get_method() == "GET")
				GET_request();
			if (request.get_method() == "DELETE")
			{}
			if (request.get_method() == "POST")
			{}
		}
		catch (std::exception &e) {
			error_flag = 1;
			std::cerr << "ERROR: " << _code << std::endl;
		}
	}
	if (error_flag){
		error_body(server);
	}
	std::cout << "BODY:\n" << _body << std::endl;
}

void HttpResponse::error_body(Server &server) {
	int flag = 0; //есть ли файл ошибки для данного кода

	if (_code == server.getErrorPageCode()){
		if (!_body.empty())
			_body.clear();
		int fd = open(server.getErrorPage().c_str(), O_RDONLY);
		if (fd < 0){
			_code = 404;
			flag = 1;
			close(fd);
		}
		else {
			close(fd);
			std::ifstream file(server.getErrorPage());
			std::getline(file, _body, '\0');
			file.close();
		}
	}
	if (flag == 1 || _code != server.getErrorPageCode())
		standart_error_body();
}

void HttpResponse::standart_error_body() {
	std::stringstream buf;

	buf << "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n"
			 "<html>\n"
			 "<head>\n"
			 "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n"
			 "<title>Пример веб-страницы</title>\n"
			 "</head>\n"
			 "<body>\n"
			 "<h1>" << _status_messages[_code] << "</h1>\n" <<
		  "_____________________" << "<h2>" << _code << "</h2>\n"
		  "</body>\n"
		  "</html>";
	_body = buf.str();
}

void HttpResponse::GET_request() {
	if (S_ISLNK(_fileInfo.st_mode) || S_ISREG(_fileInfo.st_mode)){
		std::cout << "PATH: " << _merged_path << std::endl;
		std::ifstream file;
		file.open(_merged_path);
		std::getline(file, _body, '\0');
		if (_location.client_max_body_size > _body.size()){
			_code = 413;
			throw std::exception();
		}
	}
	else{
		_code = 404;
		throw std::exception();
	}
}

void HttpResponse::init(Server &server, HttpRequest &request) {
	std::string index = get_loc(server, request);	//поиск подходящего location
	check_method(request.get_method());				//проверка на разрешенные методы
	if (_code >= 400)
		throw std::exception();

	_merged_path = _location.root;				//merged_Path - путь по которому будет искаться запрашиваемый файл
	if (_merged_path[_merged_path.length() - 1] != '/')
		_merged_path += '/';
	if (!index.empty())
		index.erase(0, 1);
	_merged_path += index;

	if (stat(_merged_path.c_str(), &_fileInfo) == -1) {  //информация о файле или диреткории по пути merged_Path
		_code = 404;
		throw std::exception();
	}

	if (S_ISDIR(_fileInfo.st_mode))						//если merged_Path папка
		check_dir(request);
}

void HttpResponse::check_dir(HttpRequest &request) {
	if (!_location.autoIndex && _location.index.empty()){
		if (!_location.autoIndex)
			_code = 403;
		else
			_code = 404;
		throw std::exception();
	}
	if (!_location.autoIndex && !_location.index.empty()){
		if (_merged_path[_merged_path.length() - 1] != '/')
			_merged_path += '/';
		_merged_path += _location.index;
		int fd = open(_merged_path.c_str(), O_RDONLY);
		if (fd < 0){
			_code = 404;
			close(fd);
			throw std::exception();
		}
		close(fd);
		stat(_merged_path.c_str(), &_fileInfo);
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

void HttpResponse::setStatusMessages() {
	_status_messages[100] = "Continue";
	_status_messages[101] = "Switching Protocols";
	_status_messages[102] = "Processing";
	_status_messages[103] = "Early Hints";
	_status_messages[200] = "OK";
	_status_messages[201] = "Created";
	_status_messages[202] = "Accepted";
	_status_messages[203] = "Non-Authoritative Information";
	_status_messages[204] = "No Content";
	_status_messages[205] = "Reset Content";
	_status_messages[206] = "Partial content";
	_status_messages[207] = "Multy-Status";
	_status_messages[300] = "Multiple Choices";
	_status_messages[301] = "Moved Permanently";
	_status_messages[302] = "Mover Temporary";
	_status_messages[307] = "Temporary Redirect";
	_status_messages[308] = "Permanent Redirect";
	_status_messages[400] = "Bad Request";
	_status_messages[401] = "Unauthorized";
	_status_messages[403] = "Forbidden";
	_status_messages[404] = "Not Found";
	_status_messages[405] = "Method Not Allowed";
	_status_messages[406] = "Not Acceptable";
	_status_messages[411] = "Length Required";
	_status_messages[413] = "Rayload Too Large";
	_status_messages[500] = "Internal Server Error";
	_status_messages[501] = "Not Implemented";
}