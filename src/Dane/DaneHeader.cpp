#include "Dane/DaneHeader.h"

std::string DaneHeader::toString() const {
	std::string s;
	s += msByte(DaneHeader::magic);
	s += lsByte(DaneHeader::magic);
	s += lsByte(DaneHeader::version);
	s += lsByte(this->encoding);
	s += msByte(this->options);
	s += lsByte(this->options);
	s += msByte(this->checksum);
	s += lsByte(this->checksum);
	return s;
}

bool DaneHeader::fromString(const std::string &s) {
	if(s.size() != DaneHeader::HEADER_SIZE) {
		return false;
	}

	auto chars = s.c_str();

	uint16_t magic = wordFromChars(chars[0], chars[1]);
	uint8_t version = chars[2];

	if(magic != DaneHeader::magic || version != DaneHeader::version) {
		return false;
	}

	this->encoding = chars[3];
	this->options = wordFromChars(chars[4], chars[5]);
	this->checksum = wordFromChars(chars[6], chars[7]);

	return true;
}
