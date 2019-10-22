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
	 * @return std::pair<bool, EncodedType> A pair representing whether the
	 * encoding succeeded and the result of the encoding operation. If the first
	 * value is false, the value of the second is undefined.
	 */
	virtual std::pair<bool, EncodedType> encode(
		const std::string &plaintext) const = 0;

	/**
	 * @brief Decodes an encoded input into a string
	 *
	 * @param encodedPlaintext An object of type EncodedType representing the
	 * encoded plaintext
	 * @return std::pair<bool, std::string> A pair representing whether the
	 * decoding succeeded and the result of the decoding operation. If the first
	 * value is false, the value of the second is undefined.
	 */
	virtual std::pair<bool, std::string> decode(
		const EncodedType &encodedPlaintext) const = 0;

	/**
	 * @brief Extracts the canonical encoding for the given plaintext and sets
	 * it as the encoding to use for future encode/decode operations
	 *
	 * @param plaintext The text to extract the encoding from
	 * @return true If the encoding was successfuly created
	 * @return false If failed in creating the encoding
	 */
	virtual bool makeEncodingFromText(const std::string &plaintext) = 0;

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
