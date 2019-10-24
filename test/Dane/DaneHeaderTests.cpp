#include "Dane/DaneHeader.h"

#include <gtest/gtest.h>
#include <sstream>

#define WORD(x, y) ((x) << 8 | (y))

TEST(DaneHeader, ToString) {
	std::string s{-38, -66, 0, 'a', 'b', 'c', 'd', 'e'};
	DaneHeader dh;
	dh.encoding = 'a';
	dh.options = WORD('b', 'c');
	dh.checksum = WORD('d', 'e');
	std::ostringstream st;
	st << dh;
	EXPECT_EQ(st.str(), s);
}

TEST(DaneHeader, FromString) {
	std::string s{-38, -66, 0, 'a', 'b', 'c', 'd', 'e'};
	std::stringstream st(s);
	DaneHeader dh;
	try {
		st >> dh;
	} catch(std::exception &e) {
		FAIL() << "operator>> threw the following exception:\n" << e.what();
	}
	ASSERT_TRUE(dh.validateHeader());
	EXPECT_EQ(dh.encoding, 'a');
	EXPECT_EQ(dh.options, WORD('b', 'c'));
	EXPECT_EQ(dh.checksum, WORD('d', 'e'));
}

TEST(DaneHeader, FromBadMagicString) {
	std::string s{-39, -66, 0, 'a', 'b', 'c', 'd', 'e'};
	std::stringstream st(s);
	DaneHeader dh;
	try {
		st >> dh;
	} catch(std::exception &e) {
		FAIL() << "operator>> threw the following exception:\n" << e.what();
	}
	ASSERT_FALSE(dh.validateHeader());
}

TEST(DaneHeader, FromBadVersionString) {
	std::string s{-38, -66, 1, 'a', 'b', 'c', 'd', 'e'};
	std::stringstream st(s);
	DaneHeader dh;
	try {
		st >> dh;
	} catch(std::exception &e) {
		FAIL() << "operator>> threw the following exception:\n" << e.what();
	}
	ASSERT_FALSE(dh.validateHeader());
}

TEST(DaneHeader, FromStringToString) {
	std::string s{-38, -66, 0, 'a', 'b', 'c', 'd', 'e'};
	std::stringstream st(s);
	DaneHeader dh;
	try {
		st >> dh;
	} catch(std::exception &e) {
		FAIL() << "operator>> threw the following exception:\n" << e.what();
	}
	ASSERT_TRUE(dh.validateHeader());
	st << dh;
	EXPECT_EQ(st.str(), s);
}

TEST(DaneHeader, FromShortString) {
	std::string s{-38, -66, 0, 'a', 'b', 'c', 'd'};
	std::stringstream st(s);
	DaneHeader dh;
	try {
		st >> dh;
		FAIL() << "operator>> was supposed to throw an exception";
	} catch(std::exception &e) {}
}
