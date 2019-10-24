#ifndef DANE_STREAM_H
#define DANE_STREAM_H

#include "Dane/DaneHeader.h"
#include "EncoderDecoder/AbstractEncoderDecoder.h"

#include <cstdint>
#include <string>
#include <type_traits>
#include <utility>

template <typename T>
class DaneStream {
protected:
	using MappingType = typename T::MappingType;
	using EncodedType = typename T::EncodedType;

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
	uint16_t calculateChecksum();

public:
	/**
	 * @brief Sets the options to be used when encoding/decoding.
	 *
	 * @param options The options to use. It's recomended to specify them using
	 * bitwise or operations on values under DaneHeader::Options::<option>.
	 */
	void setOptions(uint8_t options);
};

#endif
