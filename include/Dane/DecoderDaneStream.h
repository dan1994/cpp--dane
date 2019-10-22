#ifndef DECODER_DANE_STEAM_H
#define DECODER_DANE_STEAM_H

#include "Dane/DaneStream.h"

template <typename T>
class DecoderDaneStream : public DaneStream<T> {
private:
	bool validateDaneHeader() const;
	void parseEncodingSection(const std::string &encodingSection);
	void parseEncodedSection(const std::string &encodedSection);

public:
	DaneStream::MappingType getEncoding() const;
};

#endif
