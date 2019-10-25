#include "Dane/DaneStream.h"

template <typename T>
uint16_t DaneStream<T>::calculateChecksum() const {
	boost::crc_16_type res;
	// Process bytes before checksum
	res.process_bytes(this->encodedText.data(), 6);
	// Process bytes after checksum
	res.process_bytes(
		this->encodedText.data() + 8, this->encodedText.size() - 8);
	return res.checksum();
}

template <typename T>
void DaneStream<T>::setOptions(uint16_t options) {
	this->daneHeader.options = options;
}
