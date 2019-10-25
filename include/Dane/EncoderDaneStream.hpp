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
