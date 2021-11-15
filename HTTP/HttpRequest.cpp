//
// Created by Maya Queen on 10/27/21.
//

#include <algorithm>
#include "HttpRequest.hpp"

void HttpRequest::parse(char *buf) {
	_strBuf = std::string(buf);
	std::cout << CYAN"ALL BUFFER SIZE (BEFORE BODY BLOCK START) : " RESET << _strBuf.size() << std::endl;
	std::cout << YELLOW << _strBuf << RESET <<  std::endl;
	parseQueryString();
	parseHead();
	parseBody();
}

void HttpRequest::parseQueryString() {
	_method = std::string(_strBuf, 0, _strBuf.find(' '));
	_path = std::string(_strBuf, _method.length() + 1, _strBuf.find(' ', _method.length() + 1) - _method.length() - 1);

	std::cout << GREEN"METHOD : " RESET << _method << std::endl;// для себя
	std::cout << GREEN"PATH : " RESET << _path << std::endl;// для себя

	size_t i = 0;
	i = _path.find('?');
	if (_path.find('?') != std::string::npos)
	{
		_parameters = std::string(_path, i + 1);
		_path.erase(_path.find('?'), _path.size() - _path.find('?'));
	}
	std::cout << GREEN"URL : " RESET << _parameters << std::endl; // для себя
}

void HttpRequest::parseHead() {
	for (size_t i = _strBuf.find(CRLF, 0); _strBuf.find(BODY_SEP, i + 2) != std::string::npos ; i = _strBuf.find(CRLF, i + 2))
	{
		std::string key = std::string(_strBuf, i + 2, _strBuf.find(':', i + 2) - i - 2);
		std::string value = std::string(_strBuf, _strBuf.find(' ', i + 2) + 1, _strBuf.find(CRLF, i + 2) - i - 4 - key.length());
		std::transform(key.begin(), key.end(), key.begin(), toupper);
		_head.insert(std::pair<std::string, std::string>(key, value));
	}
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
	size_t start = _strBuf.find(BODY_SEP);
	std::cout << GREEN"HEAD END INDEX : " RESET << start << std::endl;
	start += 4;
	std::cout << GREEN"BODY START INDEX : " RESET << start << std::endl;
	if (_head.find("TRANSFER-ENCODING")->second == "chunked")
		handleChunk(start);
}

void HttpRequest::handleChunk(size_t startIndex) {
	// в этой функции обрабатываются чанки
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
