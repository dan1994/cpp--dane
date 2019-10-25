#ifndef DANE_STREAM_H
#define DANE_STREAM_H

#include "Dane/DaneHeader.h"
#include "EncoderDecoder/AbstractEncoderDecoder.h"

#include <boost/crc.hpp>
#include <cstdint>
#include <string>

template <typename T>
class DaneStream {
protected:
	using MappingType = typename T::MappingType;
	using EncodedType = typename T::EncodedType;

	struct EncodingSection {
		boost::endian::big_uint16_t sectionSize;
		boost::endian::big_uint8_t alphabetSize;
		boost::endian::big_uint8_t reserved;
	};

	struct EncodedSymbol {
		boost::endian::big_uint8_t character;
		boost::endian::big_uint8_t size;
		boost::endian::big_uint32_t representation;
	};

	DaneHeader daneHeader;
	T encoderDecoder;
	std::string plaintext;
	EncodedType encodedText;

	/**
	 * @brief Calculates a checksum over an encoded text. Ignores the bytes
	 * reserved for the checksum as specified in the dane file format.
	 *
	 * @return uint16_t The checksum
	 */
	uint16_t calculateChecksum() const;

public:
	/**
	 * @brief Sets the options to be used when encoding/decoding.
	 *
	 * @param options The options to use. It's recomended to specify them using
	 * bitwise or operations on values under DaneHeader::Options::<option>.
	 */
	void setOptions(uint16_t options);
};

#include "Dane/DaneStream.hpp"

#endif
