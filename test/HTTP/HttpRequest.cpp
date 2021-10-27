//
// Created by Maya Queen on 10/27/21.
//

#include "HttpRequest.hpp"

void HttpRequest::parse(char *buf) {
	_strBuf = std::string(buf);

	_method = std::string(_strBuf, 0, _strBuf.find(' '));
	_path = std::string (_strBuf, _method.size() + 1, _strBuf.find(' ', _method.size() + 1) - _method.size());
	if (_path.find('?') != std::string::npos)
	{
		_parameters = std::string(_path, _path.find('?'));
		_path.erase(_path.find('?'), _path.size() - _path.find('?'));
	}
	parseHead();
}

void HttpRequest::parseHead() {

}