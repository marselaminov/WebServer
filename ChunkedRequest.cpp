//
// Created by Legate Gunship on 11/15/21.
//

#include "ChunkedRequest.hpp"

ChunkedRequest::ChunkedRequest() {
	_sizeFull = false;
	_bufFull = false;
}

ChunkedRequest::~ChunkedRequest() {}

const std::string &ChunkedRequest::getStrSize() const {
	return _strSize;
}

void ChunkedRequest::setStrSize(const std::string &strSize) {
	_strSize += strSize;
}

const std::string &ChunkedRequest::getBuf() const {
	return _buf;
}

void ChunkedRequest::setBuf(const std::string &buf) {
	_buf += buf;
}

bool ChunkedRequest::isBufFull() const {
	return _bufFull;
}

void ChunkedRequest::setBufFull(bool bufFull) {
	_bufFull = bufFull;
}

bool ChunkedRequest::isSizeFull() const {
	return _sizeFull;
}

void ChunkedRequest::setSizeFull(bool sizeFull) {
	_sizeFull = sizeFull;
	if (_sizeFull == true) {
		unsigned long tmp = std::stoul(_strSize, nullptr, 16); // размер каждого чанка(куска) по документации идет в в шестнадцатеричном виде
		_castSize = static_cast<int>(tmp); // далее необходимо кастовать к инту
	}
}

int ChunkedRequest::getCastSize() const {
	return _castSize;
}

void ChunkedRequest::setCastSize(int castSize) {
	_castSize = castSize;
}
