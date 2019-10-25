#ifndef DANE_HEADER_H
#define DANE_HEADER_H

#include <boost/endian/arithmetic.hpp>
#include <cstdint>
#include <iostream>
#include <string>

class DaneHeader {
private:
	constexpr static uint16_t MAGIC = 0xdabe;
	constexpr static uint8_t VERSION = 0x0;

public:
	boost::endian::big_uint16_t magic;
	boost::endian::big_uint8_t version;
	boost::endian::big_uint8_t encoding;
	boost::endian::big_uint16_t options;
	boost::endian::big_uint16_t checksum;

	DaneHeader();

	/**
	 * @brief Checks that the header is valid. A header is valid iff its magic
	 * and version fields are equal to the precompiled constants of the class.
	 * This function DOESN'T validate the checksum, as it is over the entire
	 * file, and not over the header.
	 *
	 * @return true If the header is valid
	 * @return false Otherwise
	 */
	bool validateHeader() const;

	/**
	 * @brief Returns a string representation of the struct (Big endian)
	 *
	 * @return std::string The representation
	 */
	std::string toString() const;

	friend std::ostream &operator<<(std::ostream &os, const DaneHeader &header);
	friend std::istream &operator>>(std::istream &is, DaneHeader &header);

	class Options {
	public:
		enum EncodingOptions { EncodingOnly = 1 };
	};
};

#endif
