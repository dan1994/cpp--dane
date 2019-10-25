#include "Dane/EncoderDaneStream.h"
#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

#include <boost/endian/arithmetic.hpp>
#include <vector>

template <>
std::string EncoderDaneStream<HuffmanEncoderDecoder>::encodingToString() const {
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

	auto mapping = this->encoderDecoder.getEncoding();
	auto alphabetSize = mapping.size();
	auto sectionSize = sizeof(EncodingSection) + 6 * alphabetSize;

	EncodingSection encodingSection{sectionSize, alphabetSize, 0};

	std::vector<EncodedSymbol> encodedSymbols;
	encodedSymbols.reserve(alphabetSize);
	std::transform(mapping.begin(),
		mapping.end(),
		std::back_inserter(encodedSymbols),
		[](auto &sym) {
			return EncodedSymbol{
				sym.first, sym.second.first, sym.second.second};
		});

	std::string res(reinterpret_cast<char *>(&encodingSection));
	res += reinterpret_cast<char *>(&encodedSymbols.front());
	return res;
}

template <>
std::string EncoderDaneStream<HuffmanEncoderDecoder>::encodedToString() const {
	std::string s(this->encodedText.s);
	boost::endian::big_uint8_t bigPaddingSize = this->encodedText.paddingSize;
	s.insert(0, sizeof(bigPaddingSize), bigPaddingSize);
	return s;
}
