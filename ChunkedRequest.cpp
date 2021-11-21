//
// Created by Legate Gunship on 11/15/21.
//

#include "ChunkedRequest.hpp"

ChunkedRequest::ChunkedRequest() {
	_sizeFull = false;
	_bodyFull = false;
}

ChunkedRequest::~ChunkedRequest() {}

const std::string &ChunkedRequest::getSize() const {
	return _size;
}

void ChunkedRequest::setSize(const std::string &size) {
	_size += size;
}

const std::string &ChunkedRequest::getBody() const {
	return _body;
}

void ChunkedRequest::setBody(const std::string &body) {
	_body += body;
}

bool ChunkedRequest::isBodyFull() const {
	return _bodyFull;
}

void ChunkedRequest::setBodyFull(bool bodyFull) {
	_bodyFull = bodyFull;
}

bool ChunkedRequest::isSizeFull() const {
	return _sizeFull;
}

void ChunkedRequest::setSizeFull(bool sizeFull) {
	_sizeFull = sizeFull;
	if (_sizeFull == true) {
		unsigned long tmp = std::stoul(_size, nullptr, 16); // размер каждого чанка(куска) по документации идет в в шестнадцатеричном виде
		_castSize = static_cast<int>(tmp); // далее необходимо кастовать к инту
	}
}

int ChunkedRequest::getCastSize() const {
	return _castSize;
}

void ChunkedRequest::setCastSize(int castSize) {
	_castSize = castSize;
}
