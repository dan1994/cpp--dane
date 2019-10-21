#ifndef DANE_HEADER_H
#define DANE_HEADER_H

#include <cstdint>
#include <string>

class DaneHeader {
public:
	constexpr static int HEADER_SIZE = 8;

	constexpr static uint16_t magic = 0xdabe;
	constexpr static uint8_t version = 0x0;
	uint8_t encoding;
	uint16_t options;
	uint16_t checksum;

	std::string toString() const;
	bool fromString(const std::string &s);

	class Options {
	public:
		enum EncodingOptions { EncodingOnly = 1 };
	};
};

#endif
