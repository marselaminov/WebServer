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
	std::map<std::string, std::string> tmpEnv;

	tmpEnv["AUTH_TYPE"] = "basic";
//	tmpEnv["CONTENT_LENGTH"] = std::to_string(_request->getBody().size());

}

CGI::~CGI() {}
