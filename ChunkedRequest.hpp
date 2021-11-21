//
// Created by Legate Gunship on 11/15/21.
//

#ifndef WEBSERVER_CHUNKEDREQUEST_HPP
#define WEBSERVER_CHUNKEDREQUEST_HPP

#include <iostream>

class ChunkedRequest {
public:
	ChunkedRequest();

	virtual ~ChunkedRequest();

	const std::string &getSize() const;

	void setSize(const std::string &size);

	const std::string &getBody() const;

	void setBody(const std::string &body);

	bool isBodyFull() const;

	void setBodyFull(bool bodyFull);

	bool isSizeFull() const;

	void setSizeFull(bool sizeFull);

	int getCastSize() const;

	void setCastSize(int castSize);

private:
	std::string _size;
	std::string _body;
	bool _bodyFull;
	bool _sizeFull;
	int _castSize;
};


#endif //WEBSERVER_CHUNKEDREQUEST_HPP
