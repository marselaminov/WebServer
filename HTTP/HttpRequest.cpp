//
// Created by Maya Queen on 10/27/21.
//

#include <algorithm>
#include "HttpRequest.hpp"

void HttpRequest::parse(char *buf) {
	_strBuf = std::string(buf);
	parseQueryString();
	parseHead();
}

void HttpRequest::parseQueryString() {
	_method = std::string(_strBuf, 0, _strBuf.find(' '));
	_path = std::string(_strBuf, _method.length() + 1, _strBuf.find(' ', _method.length() + 1) - _method.length() - 1);
	if (_path.find('?') != std::string::npos)
	{
		_parameters = std::string(_path, _path.find('?') + 1);
		_path.erase(_path.find('?'), _path.size() - _path.find('?'));
	}
}

void HttpRequest::parseHead() {
	for (size_t i = _strBuf.find(CRLF, 0); _strBuf.find(BODY_SEP, i + 2) != std::string::npos ; i = _strBuf.find(CRLF, i + 2))
	{
		std::string key = std::string(_strBuf, i + 2, _strBuf.find(':', i + 2) - i - 2);
		std::string value = std::string(_strBuf, _strBuf.find(' ', i + 2) + 1, _strBuf.find(CRLF, i + 2) - i - 4 - key.length());
		std::transform(key.begin(), key.end(), key.begin(), toupper);
		_head.insert(std::pair<std::string, std::string>(key, value));
	}
}

std::string HttpRequest::get_path() {
	return _path;
}