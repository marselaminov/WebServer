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

	const std::string &getStrSize() const;

	void setStrSize(const std::string &strSize);

	const std::string &getBuf() const;

	void setBuf(const std::string &buf);

	bool isBufFull() const;

	void setBufFull(bool bufFull);

	bool isSizeFull() const;

	void setSizeFull(bool sizeFull);

	int getCastSize() const;

	void setCastSize(int castSize);

private:
	std::string _strSize;
	std::string _buf;
	bool _bufFull;
	bool _sizeFull;
	int _castSize;
};


#endif //WEBSERVER_CHUNKEDREQUEST_HPP
