#ifndef ENCODER_DANE_STREAM_H
#define ENCODER_DANE_STREAM_H

#include "Dane/DaneStream.h"

template <typename T>
class EncoderDaneStream : public DaneStream<T> {
private:
	bool extractEncodingFromText;

	std::string encodingToString() const;
	std::string encodedToString() const;
	void updateChecksum;

public:
	void makeEncodingFromText(const std::string &plaintext);
	void setEncoding(DaneStream::MappingType mapping);

	friend ostream &operator<<(ostream &os, const EncoderDaneStream &rhs);
	friend istream &operator>>(istream &is, const EncoderDaneStream &rhs);
};

#endif
