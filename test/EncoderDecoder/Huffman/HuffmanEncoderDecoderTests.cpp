#include <gtest/gtest.h>
#include <numeric>
#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

TEST(HuffmanEncoderDecoder, getFrequencies) {
	std::string s = "abca;;;7!W!!";
	std::vector<HuffmanEncoderDecoder::HuffmanNode> frequencies;
	frequencies.reserve(256);
	std::iota(frequencies.begin(), frequencies.end(), 0);
	frequencies['a'].frequency = 2;
	frequencies['b'].frequency = 1;
	frequencies['c'].frequency = 1;
	frequencies[';'].frequency = 3;
	frequencies['7'].frequency = 1;
	frequencies['!'].frequency = 3;
	frequencies['W'].frequency = 1;
	EXPECT_EQ(HuffmanEncoderDecoder::getFrequencies(s), frequencies) << "HuffmanEncoderDecoder::getFrequencies doesn't work";
}
