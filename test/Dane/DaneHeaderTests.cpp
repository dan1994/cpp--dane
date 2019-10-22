#include "Dane/DaneHeader.h"

#include <gtest/gtest.h>

TEST(DaneHeader, ToString) {
	std::string s;
	s += static_cast<char>(218);
	s += static_cast<char>(190);
	s += '\0';
	s += "abcde";
	DaneHeader dh;
	dh.encoding = 'a';
	dh.options = ('b' << 8) | 'c';
	dh.checksum = ('d' << 8) | 'e';
	EXPECT_EQ(dh.toString(), s);
}

TEST(DaneHeader, FromString) {
	std::string s;
	s += static_cast<char>(218);
	s += static_cast<char>(190);
	s += '\0';
	s += "abcde";
	DaneHeader dh;
	ASSERT_TRUE(dh.fromString(s));
	EXPECT_EQ(dh.encoding, 'a');
	EXPECT_EQ(dh.options >> 8, 'b');
	EXPECT_EQ(dh.options & 0xff, 'c');
	EXPECT_EQ(dh.checksum >> 8, 'd');
	EXPECT_EQ(dh.checksum & 0xff, 'e');
}

TEST(DaneHeader, FromBadMagicString) {
	std::string s;
	s += static_cast<char>(217);
	s += static_cast<char>(190);
	s += '\0';
	s += "abcde";
	DaneHeader dh;
	ASSERT_FALSE(dh.fromString(s));
}

TEST(DaneHeader, FromBadVersionString) {
	std::string s;
	s += static_cast<char>(218);
	s += static_cast<char>(190);
	s += static_cast<char>(1);
	s += "abcde";
	DaneHeader dh;
	ASSERT_FALSE(dh.fromString(s));
}

TEST(DaneHeader, FromStringToString) {
	std::string s;
	s += static_cast<char>(218);
	s += static_cast<char>(190);
	s += '\0';
	s += "abcde";
	DaneHeader dh;
	ASSERT_TRUE(dh.fromString(s));
	EXPECT_EQ(dh.toString(), s);
}
