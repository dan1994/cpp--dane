#ifndef PADDED_STRING_H
#define PADDED_STRING_H

#include <string>

class PaddedString {
public:
	uint8_t paddingSize;
	std::string s;
};

#endif
