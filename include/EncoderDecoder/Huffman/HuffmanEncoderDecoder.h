#ifndef HUFFMAN_ENCODER_DECODER
#define HUFFMAN_ENCODER_DECODER

#include <bits/stdc++.h>
#include "EncoderDecoder/AbstractEncoderDecoder.h"
#include "EncoderDecoder/Huffman/PaddedString.h"
#include "BiMap/BiMap.h"

class HuffmanEncoderDecoder : public AbstractEncoderDecoder {
public:
	using MappingType = BiMap<char, std::pair<unsigned char, unsigned int>>;
	using EncodedTypr = PaddedString;
	friend class HuffmanEncoderDecoder_getFrequencies_Test;

private:
	class HuffmanNode {
	public:
		char character;
		int frequency;
		std::unique_ptr<HuffmanNode> leftSon;
		std::unique_ptr<HuffmanNode> rightSon;

		HuffmanNode();
		HuffmanNode(char c);
		bool operator==(const HuffmanNode &rhs) const;
		HuffmanNode &operator++(int);
	};

	static const MappingType canonicalMapping;

	/**
	 * @brief Calculate the frequency (number of occurences) of each character in a string
	 *
	 * @param plaintext The input string
	 * @return std::vector<HuffmanNode> A vector with exactly 256 elements (1 per char value) that
	 * contains HuffmanNodes with the corresponding chars and their frequencies
	 */
	static std::vector<HuffmanNode> getFrequencies(const std::string &plaintext);

	/**
	 * @brief Create a prefixless binary tree of HuffmanNodes given a vector with the corresponding
	 * frequencies for each character
	 *
	 * @param frequencies The HuffmanNode vector
	 * @return HuffmanNode& The root of the tree
	 */
	static HuffmanNode &buildPrefixlessTree(std::vector<HuffmanNode> &frequencies);

	/**
	 * @brief Convert a prefixless binary tree into a huffman mapping
	 *
	 * @param root The root of the tree
	 * @return MappingType The huffman mapping
	 */
	static MappingType createMapping(const HuffmanNode &root);

public:
	friend std::ostream &operator<<(std::ostream &os, const HuffmanNode &);
};

#endif
