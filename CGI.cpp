//
// Created by Legate Gunship on 11/15/21.
//

#include "CGI.hpp"

CGI::CGI(Server *server, HttpRequest *request, HttpResponse *response, char *cgiPath) {
	_cgiPath = cgiPath;
	_request = request;
	_response = response;
	_bodySize = 0;
	// ----------------------------------------
	// перед запуском CGI модуля дадим значения переменным окружения
	std::map<std::string, std::string> tmpEnv;

	tmpEnv["SERVER_SOFTWARE"] = "Lions/777";
	if (!server->getServerName().empty()) {
		tmpEnv["SERVER_NAME"] = server->getServerName();
	} // содержит информацию об имени машины, на которой запущен WWW сервер, символическое имя или IP адрес соответствующие URL
	else {
		tmpEnv["SERVER_NAME"] = server->getHost();
	}
	tmpEnv["GATEWAY_INTERFACE"] = "CGI/1.1"; // содержит информацию о версии CGI(CGI/версия)
	tmpEnv["SERVER_PROTOCOL"] = "HTTP/1.1";
	tmpEnv["SERVER_PORT"] = std::to_string(server->getPort()); // начение переменной содержит номер порта, на который был послан запрос
	tmpEnv["AUTH_TYPE"] = "basic"; // значение переменной специфицирует метод аутотентификации
//	tmpEnv["CONTENT_LENGTH"] = std::to_string(_request->getBody().size()); // значение переменной соответствует длине стандартного входного потока в символах
	tmpEnv["CONTENT_TYPE"] = _request->getContentType(); // переменная специфицирована для запросов содержащих дополнительную информацию, таких как HTTP POST и PUT, и содержит тип данных этой информации
	tmpEnv["PATH_INFO"] = _request->get_path(); // значение переменной содержит полученный от клиента виртуальный путь до cgi-модуля
	tmpEnv["PATH_TRANSLATED"] = _request->get_path(); // значение переменной содержит физический путь до cgi-модуля, преобразованный из значения PATH_INFO
	tmpEnv["QUERY_STRING"] = _request->get_path() + "?" + _request->getParameters(); // значение переменной - строка символов после "?" в URL соответствующему данному запросу, эта инфа не декодируется сервером
	tmpEnv["REMOTE_ADDRESS"] = server->getHost(); // содержит IP адрес клиента
	tmpEnv["REMOTE_IDENT"] = "basic"; // содержит имя пользователя, полученное от сервера (если сервер поддерживает аутентификацию согласно RFC 931)
	tmpEnv["REMOTE_USER"] = "basic"; // содержит имя пользователя в случае аутотентификации
	tmpEnv["REQUEST_METHOD"] = _request->get_method(); // метод запроса, который был использован POST,GET и т.д.
	tmpEnv["REQUEST_URI"] = _request->get_path(); // url
	tmpEnv["SCRIPT_NAME"] = _request->get_path(); // виртуальный путь к исполняемому модулю, используемый для получения URL
	tmpEnv.insert(_request->getHead().begin(), _request->getHead().end()); // добавляем наш хед в переменнные окружения

	//----------------------------------------------------------------------------------------------------------------------
	// заполняем наше поле нашего класса (двумерный массив)
	_env = (char **) calloc(tmpEnv.size() + 1, sizeof (char *));

	std::map<std::string, std::string>::iterator it;
	size_t i = 0;
	for (it = tmpEnv.begin(); it != tmpEnv.end(); it++, i++) {
		std::string tmp = it->first + "=" + it->second;
		_env[i] = strdup(tmp.c_str());
	}

}

CGI::~CGI() {}
