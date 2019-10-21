#include "Dane/DaneHeader.h"

std::string DaneHeader::toString() const {
	std::string s;
	s += static_cast<char>(DaneHeader::magic >> 8);
	s += static_cast<char>(DaneHeader::magic);
	s += static_cast<char>(DaneHeader::version);
	s += static_cast<char>(this->encoding);
	s += static_cast<char>(this->options >> 8);
	s += static_cast<char>(this->options);
	s += static_cast<char>(this->checksum >> 8);
	s += static_cast<char>(this->checksum);
	return s;
}

bool DaneHeader::fromString(const std::string &s) {
	if(s.size() != DaneHeader::HEADER_SIZE) {
		return false;
	}

	auto chars = s.c_str();

	auto u = [](char c) { return static_cast<unsigned char>(c); };

	uint16_t magic = (u(chars[0]) << 8) | u(chars[1]);
	uint8_t version = u(chars[2]);
	uint8_t encoding = u(chars[3]);
	uint16_t options = (u(chars[4]) << 8) | u(chars[5]);
	uint16_t checksum = (u(chars[6]) << 8) | u(chars[7]);

	if(magic != DaneHeader::magic || version != DaneHeader::version) {
		return false;
	}

	this->encoding = encoding;
	this->options = options;
	this->checksum = checksum;

	return true;
}
