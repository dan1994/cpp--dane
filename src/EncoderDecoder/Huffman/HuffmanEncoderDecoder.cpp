#include <numeric>
#include <vector>
#include <algorithm>
#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

const HuffmanEncoderDecoder::MappingType HuffmanEncoderDecoder::canonicalMapping;

std::vector<HuffmanEncoderDecoder::HuffmanNode> HuffmanEncoderDecoder::getFrequencies(const std::string &plaintext) {

	// Initialize frequencies
	std::vector<HuffmanNode> frequencies;
	frequencies.reserve(256);
	std::iota(frequencies.begin(), frequencies.end(), 0);

	// Count frequency of each char in plaintext
	std::for_each(plaintext.cbegin(), plaintext.cend(), [&](auto c) {
		frequencies[c]++;
	});

	return frequencies;
}
