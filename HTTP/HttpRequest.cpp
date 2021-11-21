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
//	std::cout << GREEN"HEAD END INDEX : " RESET << start << std::endl;
//	start += 4;
//	std::cout << GREEN"BODY START INDEX : " RESET << start << std::endl;
	if (_head.find("TRANSFER-ENCODING")->second == "chunked")
		handleChunk();
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

void HttpRequest::handleChunk() {
	size_t startBody = _strBuf.find(BODY_SEP) + 4;
	size_t endBody = _strBuf.find("0\r\n\r\n", startBody); // окончание передачи сообщения определяется наличием последней части с нулевой длиной (0\r\n\r\n)
	_body = std::string(_strBuf, startBody, endBody - startBody + 3); // записали тело запроса (+3 потому что <длина блока в HEX><CRLF>)
	// --------------------------------------------------------------------------------------
	// дальше создание вектора чанков
	size_t i = 0;
	while (i < _body.size()) { // пробегаемся по циклу по не дойдем до конца тела запроса
		size_t crlf = 0;
		ChunkedRequest *chunk = new ChunkedRequest(); // на каждую часть запроса создаем объект чанка
		_chunk.push_back(chunk); // и закидываем его в вектор
		// считываем размер каждого чанка
		if ((crlf = _body.find(CRLF, i)) != std::string::npos) {
			if (!_chunk.back()->isSizeFull()) {
				std::string chunkSize = std::string(_body, i, (crlf - i));
				_chunk.back()->setSize(chunkSize); // временно записываем размер в строку
				try {
					_chunk.back()->setSizeFull(true); // в данном методе кастуем размер к инту
				}
				catch (std::exception &e) {
					std::cerr << "Some error chunk size" << std::endl;
					_state = PARSE_FINISH;
					break;
				}
				if (_chunk.back()->getCastSize() == 0) { // проверяем не конец ли тела запроса (конец тела запроса символизируется нулем)
					_chunk.back()->setBodyFull(true); // сатвим флаг об окончании и выходим из цикла
					_state = PARSE_FINISH;
					break;
				}
				i = i + crlf + 2 - i; // + 2 crlf - позиция (переходим к содержимому чанка)
			}
		}
		// и читаем содержимое чанка
		if ((crlf = _body.find(CRLF, i)) != std::string::npos) {
			if (!_chunk.back()->isBodyFull()) {
				size_t sizeTmpBody = static_cast<size_t>(_chunk.back()->getCastSize());
				std::string tmpBody = std::string(_body, i, sizeTmpBody);
				_chunk.back()->setBody(tmpBody); // записываем содержимое чанка
				_chunk.back()->setBodyFull(true); // ставим флажок что заполнили
				i = i + _chunk.back()->getBody().size() + 2; // переходим к следующему блоку чанка (позиция  + размер чанка + 2 crlf
			}
		}
	}
	// --------------------------------------------------------------------------------------
	// читстим тело запроса и пересаписываем его из сформированных частей
	_body.clear();
	for (size_t j = 0; j < _chunk.size(); ++j) {
		size_t bodySize = static_cast<size_t>(_chunk[j]->getCastSize());
		_body += std::string(_chunk[j]->getBody(), 0, bodySize);
	}
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