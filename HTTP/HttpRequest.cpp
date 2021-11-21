//
// Created by Maya Queen on 10/27/21.
//

#include <algorithm>
#include "HttpRequest.hpp"

HttpRequest::HttpRequest() : _state(PARSE_QUERY_STR){
}

void HttpRequest::clear() {
	_strBuf.clear();
	_method.clear();
	_path.clear();
	_parameters.clear();
	_head.clear();
	_body.clear();
	_state = PARSE_QUERY_STR;
}

void HttpRequest::parse(char *buf, size_t bytes_read) {
	_strBuf.append(buf, bytes_read);
	std::cout << CYAN"ALL BUFFER SIZE (BEFORE BODY BLOCK START) : " RESET << _strBuf.size() << std::endl;
//	std::cout << YELLOW << _strBuf << RESET <<  std::endl;
	switch (_state) {
		case PARSE_QUERY_STR:
			parseQueryString();
		case PARSE_HEAD:
			parseHead();
		case PARSE_BODY:
			parseBody();
	}
}

void HttpRequest::parseQueryString() {
	_method = std::string(_strBuf, 0, _strBuf.find(' '));
	_path = std::string(_strBuf, _method.length() + 1, _strBuf.find(' ', _method.length() + 1) - _method.length() - 1);

	std::cout << GREEN"METHOD : " RESET << _method << std::endl;// для себя
	std::cout << GREEN"PATH : " RESET << _path << std::endl;// для себя

	size_t i;
	i = _path.find('?');
	if (_path.find('?') != std::string::npos)
	{
		_parameters = std::string(_path, i + 1);
		_path.erase(_path.find('?'), _path.size() - _path.find('?'));
	}
	std::cout << GREEN"PARAMETERS : " RESET << _parameters << std::endl; // для себя
	_state = PARSE_HEAD;
}

void HttpRequest::parseHead() {
	for (size_t i = _strBuf.find(CRLF, 0); _strBuf.find(BODY_SEP, i + 2) != std::string::npos ; i = _strBuf.find(CRLF, i + 2))
	{
		std::string key = std::string(_strBuf, i + 2, _strBuf.find(':', i + 2) - i - 2);
		std::string value = std::string(_strBuf, _strBuf.find(' ', i + 2) + 1, _strBuf.find(CRLF, i + 2) - i - 4 - key.length());
		std::transform(key.begin(), key.end(), key.begin(), toupper);
		_head.insert(std::pair<std::string, std::string>(key, value));
	}
	_state = PARSE_BODY;
	// код ниже для себя (печатаю содержимое мапы head)
	std::cout << GREEN"HEAD:" RESET << std::endl;
	std::map<std::string, std::string>::const_iterator it;
	it = _head.begin();
	while (it != _head.end()) {
		std::cout << it->first << " : " << it->second << " " << std::endl;
		++it;
	}
}

void HttpRequest::parseBody() {
//	size_t start = _strBuf.find(BODY_SEP);
//	std::cout << GREEN"HEAD END INDEX : " RESET << start << std::endl;
//	start += 4;
//	std::cout << GREEN"BODY START INDEX : " RESET << start << std::endl;
	if (_head.find("TRANSFER-ENCODING")->second == "chunked")
		handleChunk(0);
	else if (_head.find("CONTENT-LENGTH") != _head.end())
		handleContentBody();
	else
		_state = PARSE_FINISH;
}

void HttpRequest::handleContentBody() {
	int cont_len = stoi(_head["CONTENT-LENGTH"]);

	if (_strBuf.length() - _strBuf.find(BODY_SEP) - 4 == cont_len){

		_body = std::string (_strBuf, _strBuf.find(BODY_SEP) + 4, cont_len);
		std::cout << "BODY:\n" << _body << std::endl;
		_state = PARSE_FINISH;
	}
}

void HttpRequest::handleChunk(size_t startIndex) {
	// в этой функции обрабатываются чанки
	_state = PARSE_FINISH;
}

std::string HttpRequest::get_path() {
	return _path;
}

std::string HttpRequest::get_method() {
	return _method;
}

const std::map<std::string, std::string> &HttpRequest::getHead() const {
	return _head;
}

const std::string &HttpRequest::getParameters() const {
	return _parameters; // query string
}

RequestStates HttpRequest::getState() {
	return _state;
}

std::string HttpRequest::getContentType() {
	if (_head.find("CONTENT_TYPE") == _head.end())
		return ("text/html"); // если нет значения
	else
		return (_head.at("CONTENT_TYPE")); // достаем значение по ключу
}

void HttpRequest::setContentType(std::string contentType) {
	_head["CONTENT-TYPE"] = contentType;
}