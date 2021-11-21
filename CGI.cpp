//
// Created by Legate Gunship on 11/15/21.
//

#include "CGI.hpp"

CGI::CGI(Server *server, HttpRequest *request, std::string cgiPath) {
	_cgiPath = cgiPath;
	_request = request;
	_bodySize = 0;
	// ----------------------------------------
	// перед запуском CGI модуля дадим значения переменным окружения
	std::map<std::string, std::string> tmpEnv;

	tmpEnv["SERVER_SOFTWARE"] = "Lions/777";
//	if (!server->getServerName().empty()) {
//		tmpEnv["SERVER_NAME"] = server->getServerName();
//	} // содержит информацию об имени машины, на которой запущен WWW сервер, символическое имя или IP адрес соответствующие URL
//	else {
//		tmpEnv["SERVER_NAME"] = server->getHost();
//	}
	tmpEnv["GATEWAY_INTERFACE"] = "CGI/1.1"; // содержит информацию о версии CGI(CGI/версия)
	tmpEnv["SERVER_PROTOCOL"] = "HTTP/1.1";
	tmpEnv["SERVER_PORT"] = std::to_string(server->getPort()); // значение переменной содержит номер порта, на который был послан запрос
	tmpEnv["AUTH_TYPE"] = "basic"; // значение переменной специфицирует метод аутентификации
//	tmpEnv["CONTENT_LENGTH"] = std::to_string(_request->getBody().size()); // значение переменной соответствует длине стандартного входного потока в символах
	tmpEnv["CONTENT_TYPE"] = _request->getContentType(); // переменная специфицирована для запросов содержащих дополнительную информацию, таких как HTTP POST и PUT, и содержит тип данных этой информации
	tmpEnv["PATH_INFO"] = _request->get_path(); // значение переменной содержит полученный от клиента виртуальный путь до cgi-модуля
	tmpEnv["PATH_TRANSLATED"] = _request->get_path(); // значение переменной содержит физический путь до cgi-модуля, преобразованный из значения PATH_INFO
	tmpEnv["QUERY_STRING"] = _request->get_path() + "?" + _request->getParameters(); // значение переменной - строка символов после "?" в URL соответствующему данному запросу, эта инфа не декодируется сервером
	tmpEnv["REMOTE_ADDRESS"] = server->getHost(); // содержит IP адрес клиента
	tmpEnv["REMOTE_IDENT"] = "basic"; // содержит имя пользователя, полученное от сервера (если сервер поддерживает аутентификацию согласно RFC 931)
	tmpEnv["REMOTE_USER"] = "basic"; // содержит имя пользователя в случае аутентификации
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
	tmpEnv.clear();
	//----------------------------------------------------------------------------------------------------------------------
	// execute CGI part (execute cgi script with execve and forked process)
	exec();
	handleBody();
}

void CGI::handleBody() { //text/html; charset=utf-8
	size_t i;
	std::string cgiHead;
	if (_body.find(BODY_SEP, 0) != std::string::npos) { // если находим два переноса строки то заходим в условие
		i = _body.find(BODY_SEP, 0); // ищем конец заголовка запроса
		cgiHead = std::string(_body, 0, (i + 4)); // записываем в head
		_body = std::string(_body, (i + 4)); // перезаписываем тело запроса
		if (cgiHead.find("Status: ") != std::string::npos)
//			_response->setCode(std::atoi(cgiHead.substr(8, 3).c_str()));
			_code = std::atoi(cgiHead.substr(8, 3).c_str());
		if ((i = cgiHead.find("Content-Type: ", 0)) != std::string::npos)
			_request->setContentType(cgiHead.substr(i + 14, 24)); // //text/html; charset=utf-8 (24 chars)
//		size_t bodySize = static_cast<size_t>(_bodySize);
//		_response->setBodySize(bodySize - cgiHead.size()); // записываем размер тела
		_bodySizeForReturn = static_cast<size_t>(_bodySize) - cgiHead.size();
	}
}

CGI::~CGI() {}

void CGI::exec() {
	FILE *file[2]; // переменная, в которую будет сохранен указатель на управляющую таблицу открываемого потока данных
	pid_t pid; // для создания дочернего процесса
	int oldFd[2]; // для сохранения старого дескриптора и подмены
	int fileFd[2]; // дескриптор файловых потоков

	// создаем копии наших потоков ввода и выводв и сохраяем
	oldFd[0] = dup(0);
	oldFd[1] = dup(1);
	if (oldFd[0] == -1 || oldFd[1] == -1)
		throw std::runtime_error("Error saving file descriptor");

	// создаем файловый поток данных
	file[0] = tmpfile();
	file[1] = tmpfile();
	if (!file[0] || !file[1])
		throw std::runtime_error("Error creating file for temporary work");

	// определяем дескриптор файла, связанного с файловым потоком данных
	fileFd[0] = fileno(file[0]);
	fileFd[1] = fileno(file[1]);
	if (fileFd[0] == -1 || fileFd[1] == -1)
		throw std::runtime_error("Error creating file descriptor");

	// записываем во входящий поток наш body
	write(fileFd[0], _request->getBody().c_str(), _request->getBody().size());
	// перемещаем указатель в начало файла
	lseek(fileFd[0], 0, 0);

	// создаем дочерний процесс
	pid = fork();
	if (pid == -1) { // если дочерний процесс не создался
		_code = 500;
		throw std::runtime_error("Error forking parent process");
	}
	else if (pid == 0) { //
		dup2(fileFd[0], 0); // подменяем наши дескрипторы для запуска программы
		dup2(fileFd[1], 1);
		// запускаем нашу cgi программу в дочернем процессе, в случае успеха код уже ниже условия не пойдет
		if (execve(_cgiPath.c_str(), NULL, _env) == -1)
			throw std::runtime_error("Error executing child process");
		std::cerr << "Error status: 500" << std::endl;
	}
	else {
		wait(NULL); // ожидаем завершения дочернего процесса и продолжаем работу уже в родит процессе
		char buff[10000];
		lseek(fileFd[1], 0, 0); // перемещаем указатель в начало файла
		ssize_t bytes = 1;
		while (bytes > 0) { // считываем пока не ошибка(-1) или не конец файла(0)
			bzero(buff, 10000); // очищаем наш буфер , в который считываем из файлового потока
			bytes = read(fileFd[1], buff, 10000); // считываем в буфер 10000 байт
			_bodySize += bytes; // определяем размер тела
			_body += buff; // записываем само тело запроса в стрингу
		}
	}

	// подменяем дескрипторы
	dup2(oldFd[0], 0);
	dup2(oldFd[1], 1);
	// закрываем файловые потоки
	fclose(file[0]);
	fclose(file[1]);
	// закрываем дескрипторы
	close(fileFd[0]);
	close(fileFd[1]);
	close(oldFd[0]);
	close(oldFd[1]);

	// проверяем нет ли процесса zombie (незавершенный дочерний процесс)
	if (pid == 0)
		exit(0);
}

const std::string &CGI::getBody() const {
	return _body;
}

int CGI::getCode() const {
	return _code;
}

size_t CGI::getBodySizeForReturn() const {
	return _bodySizeForReturn;
}
