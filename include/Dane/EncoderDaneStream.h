#ifndef ENCODER_DANE_STREAM_H
#define ENCODER_DANE_STREAM_H

#include "Dane/DaneStream.h"

template <typename T>
class EncoderDaneStream : public DaneStream<T> {
private:
	using MappingType = typename DaneStream<T>::MappingType;

	bool extractEncodingFromText;

	std::string encodingToString() const;
	std::string encodedToString() const;
	void updateChecksum();

public:
	void makeEncodingFromText(const std::string &plaintext);
	void setEncoding(MappingType mapping);

	friend ostream &operator<<(ostream &os, const EncoderDaneStream &rhs);
	friend istream &operator>>(istream &is, EncoderDaneStream &rhs);
};

#include "Dane/EncoderDaneStream.hpp"

#endif
