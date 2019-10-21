#include "Dane/DaneHeader.h"

#include <gtest/gtest.h>

TEST(DaneHeader, ToString) {
	DaneHeader dh;
	dh.encoding = 'a';
	dh.options = ('b' << 8) | 'c';
	dh.checksum = ('d' << 8) | 'e';
	std::string s;
	s += static_cast<char>(218);
	s += static_cast<char>(190);
	s += '\0';
	s += "abcde";
	EXPECT_EQ(dh.toString(), s);
}

TEST(DaneHeader, FromString) {
	std::string s;
	s += static_cast<unsigned char>(218);
	s += static_cast<unsigned char>(190);
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
