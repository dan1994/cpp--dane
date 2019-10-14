#include <gtest/gtest.h>
#include <numeric>
#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

TEST(HuffmanEncoderDecoder, getFrequencies) {
	std::string s = "abca;;;7!W!!";
	auto frequencies = HuffmanEncoderDecoder::getFrequencies(s);
	EXPECT_EQ(frequencies['a']->frequency, 2);
	EXPECT_EQ(frequencies['b']->frequency, 1);
	EXPECT_EQ(frequencies['c']->frequency, 1);
	EXPECT_EQ(frequencies[';']->frequency, 3);
	EXPECT_EQ(frequencies['7']->frequency, 1);
	EXPECT_EQ(frequencies['!']->frequency, 3);
	EXPECT_EQ(frequencies['W']->frequency, 1);
}
