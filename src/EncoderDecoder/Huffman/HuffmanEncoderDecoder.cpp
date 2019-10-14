#include <numeric>
#include <vector>
#include <algorithm>
#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

const HuffmanEncoderDecoder::MappingType HuffmanEncoderDecoder::canonicalMapping;

HuffmanEncoderDecoder::NodeVector HuffmanEncoderDecoder::getFrequencies(const std::string &plaintext) {

	// Initialize frequencies
	NodeVector frequencies;
	frequencies.reserve(256);
	std::generate(frequencies.begin(), frequencies.begin() + 256, []() {
		static char c = 0;
		return std::make_unique<Node>(Node(c++));
	});

	// Count frequency of each char in plaintext
	std::for_each(plaintext.cbegin(), plaintext.cend(), [&](auto c) {
		auto &fp = frequencies[c];
		(*fp)++;
	});

	return frequencies;
}
