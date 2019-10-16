#include <gtest/gtest.h>
#include <numeric>
#include "Pair/Hash.h"
#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

TEST(HuffmanEncoderDecoder, makeEncodingFromTextSubRoutines) {
	std::string s = "abca;;;c;c!c!c!!!!";
	auto frequencies = HuffmanEncoderDecoder::getFrequencies(s);
	EXPECT_EQ(frequencies['a']->frequency, 2);
	EXPECT_EQ(frequencies['b']->frequency, 1);
	EXPECT_EQ(frequencies['c']->frequency, 5);
	EXPECT_EQ(frequencies[';']->frequency, 4);
	EXPECT_EQ(frequencies['!']->frequency, 6);

	auto tree = HuffmanEncoderDecoder::buildPrefixlessTree(frequencies);
	/*
	           18
	     7            11
	  3     4      5      6
	1   2
	*/
	ASSERT_NE(tree, nullptr) << "\nbuildPrefixlessTree returned a nullptr\n";
	EXPECT_EQ(tree->frequency, 18);
	EXPECT_EQ(tree->character, 0);
	EXPECT_EQ(tree->leftSon->frequency, 7);
	EXPECT_EQ(tree->leftSon->character, 0);
	EXPECT_EQ(tree->leftSon->leftSon->frequency, 3);
	EXPECT_EQ(tree->leftSon->leftSon->character, 0);
	EXPECT_EQ(tree->leftSon->leftSon->leftSon->frequency, 1);
	EXPECT_EQ(tree->leftSon->leftSon->leftSon->character, 'b');
	EXPECT_EQ(tree->leftSon->leftSon->rightSon->frequency, 2);
	EXPECT_EQ(tree->leftSon->leftSon->rightSon->character, 'a');
	EXPECT_EQ(tree->leftSon->rightSon->frequency, 4);
	EXPECT_EQ(tree->leftSon->rightSon->character, ';');
	EXPECT_EQ(tree->rightSon->frequency, 11);
	EXPECT_EQ(tree->rightSon->character, 0);
	EXPECT_EQ(tree->rightSon->leftSon->frequency, 5);
	EXPECT_EQ(tree->rightSon->leftSon->character, 'c');
	EXPECT_EQ(tree->rightSon->rightSon->frequency, 6);
	EXPECT_EQ(tree->rightSon->rightSon->character, '!');

	auto mapping = HuffmanEncoderDecoder::createMapping(tree);
	EXPECT_EQ(mapping.atT('b'), (std::make_pair<unsigned char, unsigned int>(3, 0)));
	EXPECT_EQ(mapping.atT('a'), (std::make_pair<unsigned char, unsigned int>(3, 1)));
	EXPECT_EQ(mapping.atT(';'), (std::make_pair<unsigned char, unsigned int>(2, 1)));
	EXPECT_EQ(mapping.atT('c'), (std::make_pair<unsigned char, unsigned int>(2, 2)));
	EXPECT_EQ(mapping.atT('!'), (std::make_pair<unsigned char, unsigned int>(2, 3)));
}
