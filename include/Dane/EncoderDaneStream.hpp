#include "Dane/EncoderDaneStream.h"

template <typename T>
void EncoderDaneStream<T>::updateChecksum() {
	this->daneHeader.checksum = this->calculateChecksum();
}

template <typename T>
void EncoderDaneStream<T>::makeEncodingFromText(const std::string &plaintext) {
	this->encoderDecoder.makeEncodingFromText(plaintext);
}

template <typename T>
void EncoderDaneStream<T>::setEncoding(MappingType mapping) {
	this->encoderDecoder.setEncoding(std::move(mapping));
}

template <typename T>
std::ostream &operator<<(std::ostream &os, EncoderDaneStream<T> &rhs) {
	rhs.encodedText = rhs.encoderDecoder.encode(rhs.plaintext);
	return os << rhs.daneHeader << rhs.encodingToString()
			  << rhs.encodedToString();
}

template <typename T>
std::istream &operator>>(std::istream &is, EncoderDaneStream<T> &rhs) {
	constexpr BUF_SIZE = 128;
	char buf[BUF_SIZE];
	auto count = 0;
	do {
		is.read(buf, BUF_SIZE - 1);
		count = is.gcount();
		rhs.plaintext.append(count, buf);
	} while(count > 0)
}
