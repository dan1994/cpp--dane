#include "Dane/DaneHeader.h"

DaneHeader::DaneHeader() :
	magic(MAGIC), version(VERSION), encoding(0), options(0), checksum(0) {}

bool DaneHeader::validateHeader() const {
	return this->magic == DaneHeader::MAGIC &&
		this->version == DaneHeader::VERSION;
}

std::string DaneHeader::toString() const {
	return std::string(
		reinterpret_cast<const char *>(this), sizeof(DaneHeader));
}

std::ostream &operator<<(std::ostream &os, const DaneHeader &header) {
	return os << header.toString();
}

std::istream &operator>>(std::istream &is, DaneHeader &header) {
	char *s = reinterpret_cast<char *>(&header);
	std::istream &is2 = is.read(s, sizeof(header));
	if(is.gcount() != sizeof(header)) {
		throw std::length_error("Not enough bytes to construct Dane Header");
	}
	return is2;
}
