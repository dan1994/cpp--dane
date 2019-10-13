#ifndef HUFFMAN_ENCODER_DECODER
#define HUFFMAN_ENCODER_DECODER

#include <utility>
#include <memory>
#include <list>
#include "EncoderDecoder/AbstractEncoderDecoder.h"
#include "EncoderDecoder/Huffman/PaddedString.h"
#include "BiMap/BiMap.h"

class HuffmanEncoderDecoder : public AbstractEncoderDecoder {
public:
	using MappingType = BiMap<char, std::pair<unsigned char, unsigned int>>;
	using EncodedTypr = PaddedString;

private:
	class HuffmanNode {
	public:
		const char character;
		const int frequency;
		std::unique_ptr<HuffmanNode> leftSon;
		std::unique_ptr<HuffmanNode> rightSon;
		HuffmanNode(char character, int frequency);
	};

	static const MappingType canonicalMapping;
	static std::list<HuffmanNode> getFrequencies(const std::string &plaintext);
	static HuffmanNode &buildPrefixlessTree(std::list<HuffmanNode> &frequencies);
	static MappingType createMapping(const HuffmanNode &root);
};

#endif
