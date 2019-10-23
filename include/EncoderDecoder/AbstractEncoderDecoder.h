#ifndef ABSTRACT_ENCODER_DECODER_H
#define ABSTRACT_ENCODER_DECODER_H

#include <string>

template <typename M, typename E>
class AbstractEncoderDecoder {
public:
	using MappingType = M;
	using EncodedType = E;

	/**
	 * @brief Encodes a given plaintext string.
	 *
	 * @param plaintext String to encode
	 * @return EncodedType The result of the encoding operation.
	 */
	virtual EncodedType encode(const std::string &plaintext) const = 0;

	/**
	 * @brief Decodes an encoded input into a string
	 *
	 * @param encodedText An object of type EncodedType representing the
	 * encoded text
	 * @return std::string The decoded plaintext
	 */
	virtual std::string decode(const EncodedType &encodedText) const = 0;

	/**
	 * @brief Extracts the canonical encoding for the given plaintext and sets
	 * it as the encoding to use for future encode/decode operations
	 *
	 * @param plaintext The text to extract the encoding from
	 */
	virtual void makeEncodingFromText(const std::string &plaintext) = 0;

	/**
	 * @brief Sets the encoding to use to the given encoding
	 *
	 * @param mapping The encoding to use
	 */
	virtual void setEncoding(MappingType mapping) = 0;

	/**
	 * @brief Get the currently used encoding
	 *
	 * @return const MappingType& The encoding
	 */
	virtual const MappingType &getEncoding() const = 0;
};

#endif
