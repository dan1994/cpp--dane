#ifndef PADDED_STRING_H
#define PADDED_STRING_H

#include <string>

struct PaddedString {
	std::string s;
	uint8_t paddingSize;
};

#endif
