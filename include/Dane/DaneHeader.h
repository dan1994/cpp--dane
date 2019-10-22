#ifndef DANE_HEADER_H
#define DANE_HEADER_H

#include <cstdint>
#include <string>

class DaneHeader {
private:
	static constexpr auto msByte = [](auto x) -> unsigned char {
		return x >> std::numeric_limits<unsigned char>::digits;
	};

	static constexpr auto lsByte = [](auto x) -> unsigned char {
		return x & 0xff;
	};

	static constexpr auto wordFromChars = [](unsigned char ms,
											  unsigned char ls) -> uint16_t {
		return (ms << std::numeric_limits<unsigned char>::digits) | ls;
	};

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
