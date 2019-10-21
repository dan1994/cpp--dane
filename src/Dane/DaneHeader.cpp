#include "Dane/DaneHeader.h"

std::string DaneHeader::toString() const {
	char arr[] = {DaneHeader::magic >> 8,
		DaneHeader::magic,
		DaneHeader::version,
		this->encoding,
		this->options,
		this->checksum >> 8,
		this->checksum,
		0};
	return std::string(std::move(arr));
}

bool DaneHeader::fromString(const std::string &s) {
	if(s.size() != DaneHeader::HEADER_SIZE) {
		return false;
	}

	auto chars = s.c_str();

	uint16_t magic = (chars[0] << 8) | chars[1];
	uint8_t version = chars[2];
	uint8_t encoding = chars[3];
	uint16_t options = (chars[4] << 8) | chars[5];
	uint16_t checksum = (chars[6] << 8) | chars[7];

	if(magic != DaneHeader::magic || version != DaneHeader::version) {
		return false;
	}

	this->encoding = encoding;
	this->options = options;
	this->checksum = checksum;

	return true;
}
