#include <gtest/gtest.h>
#include <random>
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

TEST(HuffmanEncoderDecoder, makeEncodingFromText) {
	std::string s = "abca;;;c;c!c!c!!!!";
	HuffmanEncoderDecoder hed;
	hed.makeEncodingFromText(s);
	auto &mapping = hed.getEncoding();
	EXPECT_EQ(mapping.atT('b'), (std::make_pair<unsigned char, unsigned int>(3, 0)));
	EXPECT_EQ(mapping.atT('a'), (std::make_pair<unsigned char, unsigned int>(3, 1)));
	EXPECT_EQ(mapping.atT(';'), (std::make_pair<unsigned char, unsigned int>(2, 1)));
	EXPECT_EQ(mapping.atT('c'), (std::make_pair<unsigned char, unsigned int>(2, 2)));
	EXPECT_EQ(mapping.atT('!'), (std::make_pair<unsigned char, unsigned int>(2, 3)));
}

TEST(HuffmanEncoderDecoder, SetEncoding) {
	HuffmanEncoderDecoder hed;
	HuffmanEncoderDecoder::MappingType m;
	m.insert('a', std::make_pair(1, 0));
	m.insert('b', std::make_pair(1, 1));
	hed.setEncoding(m);
	auto &m2 = hed.getEncoding();
	EXPECT_EQ(m2.atT('a'), m.atT('a'));
	EXPECT_EQ(m2.atT('b'), m.atT('b'));
}

TEST(HuffmanEncoderDecoder, IdentityEncoding) {
	HuffmanEncoderDecoder hed;
	HuffmanEncoderDecoder::MappingType m;
	ASSERT_TRUE(m.insert('a', std::make_pair(8, 'a')));
	ASSERT_TRUE(m.insert('b', std::make_pair(8, 'b')));
	ASSERT_TRUE(m.insert('c', std::make_pair(8, 'c')));
	hed.setEncoding(m);
	std::string s = "aabcbbc";
	auto [success, encodedText] = hed.encode(s);
	ASSERT_TRUE(success) << "Failed encoding";
	EXPECT_EQ(encodedText.s, s);
}

TEST(HuffmanEncoderDecoder, Plus1Encoding) {
	HuffmanEncoderDecoder hed;
	HuffmanEncoderDecoder::MappingType m;
	ASSERT_TRUE(m.insert('a', std::make_pair(8, 'b')));
	ASSERT_TRUE(m.insert('b', std::make_pair(8, 'c')));
	ASSERT_TRUE(m.insert('c', std::make_pair(8, 'd')));
	hed.setEncoding(m);
	std::string s = "aabcbbc";
	std::string encodedS;
	std::transform(s.begin(), s.end(), std::back_inserter(encodedS), [](char c) { return ++c; });
	auto [success, encodedText] = hed.encode(s);
	ASSERT_TRUE(success) << "Failed encoding";
	EXPECT_EQ(encodedText.s, encodedS);
}

TEST(HuffmanEncoderDecoder, ActualEncoding) {
	HuffmanEncoderDecoder hed;
	HuffmanEncoderDecoder::MappingType m;
	ASSERT_TRUE(m.insert('a', std::make_pair(1, 0)));
	ASSERT_TRUE(m.insert('b', std::make_pair(2, 2)));
	ASSERT_TRUE(m.insert('c', std::make_pair(2, 3)));
	hed.setEncoding(m);
	std::string s = "aabcbbc";
	// 00101110 1011
	unsigned char encodedS[3] = {46, 176, 0};
	auto [success, encodedText] = hed.encode(s);
	ASSERT_TRUE(success) << "Failed encoding";
	EXPECT_EQ(encodedText.s, std::string(reinterpret_cast<char *>(encodedS)));
}

TEST(HuffmanEncoderDecoder, EncodeDecode) {
	HuffmanEncoderDecoder hed;
	HuffmanEncoderDecoder::MappingType m;
	ASSERT_TRUE(m.insert('a', std::make_pair(1, 0)));
	ASSERT_TRUE(m.insert('b', std::make_pair(2, 2)));
	ASSERT_TRUE(m.insert('c', std::make_pair(2, 3)));
	hed.setEncoding(m);
	std::string s = "aabcbbc";
	auto [success, encodedText] = hed.encode(s);
	ASSERT_TRUE(success) << "Failed encoding";
	auto [success2, plaintext] = hed.decode(encodedText);
	ASSERT_TRUE(success2) << "Failed decoding";
	EXPECT_EQ(plaintext, s) << "decode(encode(s)) != s";
}

TEST(HuffmanEncoderDecoder, EncodeDecodeRandomString) {
	HuffmanEncoderDecoder hed;
	std::string s = "";
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<unsigned char> dist(0, 255);
	for(int i = 0; i < 10000; i++) {
		s += dist(mt);
	}
	hed.makeEncodingFromText(s);
	auto [success, encodedText] = hed.encode(s);
	ASSERT_TRUE(success) << "Failed encoding";
	auto [success2, plaintext] = hed.decode(encodedText);
	ASSERT_TRUE(success2) << "Failed decoding";
	EXPECT_EQ(plaintext, s) << "decode(encode(s)) != s";
}
