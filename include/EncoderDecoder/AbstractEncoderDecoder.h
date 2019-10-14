#ifndef ABSTRACT_ENCODER_DECODER_H
#define ABSTRACT_ENCODER_DECODER_H

#include <string>

class AbstractEncoderDecoder {
public:
	using MappingType = void *;
	using EncodedType = void *;

protected:
	bool usingCanonicalEncoding;
	MappingType mapping;

public:
	/**
	 * @brief Encodes a given plaintext string.
	 *
	 * @param plaintext String to encode
	 * @return EncodedType An object that represents the encoding of plaintext
	 */
	virtual EncodedType encode(const std::string &plaintext) const = 0;

	/**
	 * @brief Decodes an encoded input into a string
	 *
	 * @param encodedPlaintext An object of type EncodedType representing the encoded plaintext
	 * @return std::string The decoded string
	 */
	virtual std::string decode(const EncodedType &encodedPlaintext) const = 0;

	/**
	 * @brief Sets the canonical encoding as the encoding to use for future encode/decode
	 * operations
	 *
	 */
	virtual void useCanonicalEncoding() = 0;

	/**
	 * @brief Extracts the optimal encoding for the given plaintext and sets it as the encoding to
	 * use for future encode/decode operations
	 *
	 * @param plaintext The text to extract the encoding from
	 */
	virtual void makeEncodingFromText(const std::string &plaintext) = 0;

	/**
	 * @brief Sets the encoding to use to the given encoding
	 *
	 * @param mapping The encoding to use
	 */
	virtual void setEncoding(MappingType &&mapping) = 0;

	/**
	 * @brief Get the currently used encoding
	 *
	 * @return const MappingType& The encoding
	 */
	virtual const MappingType &getEncoding() = 0;
};

#endif
