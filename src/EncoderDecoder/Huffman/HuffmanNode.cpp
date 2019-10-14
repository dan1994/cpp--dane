#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

HuffmanEncoderDecoder::HuffmanNode::HuffmanNode() : HuffmanNode(0) {}

HuffmanEncoderDecoder::HuffmanNode::HuffmanNode(char c) :
	character(c), frequency(0), leftSon(nullptr), rightSon(nullptr) {}

bool HuffmanEncoderDecoder::HuffmanNode::operator==(const HuffmanNode &rhs) const {
	return (this->character == rhs.character) && (this->frequency == rhs.frequency);
}

HuffmanEncoderDecoder::HuffmanNode &HuffmanEncoderDecoder::HuffmanNode::operator++(int) {
	this->frequency++;
	return *this;
}

std::ostream &operator<<(std::ostream &os, const HuffmanEncoderDecoder::HuffmanNode &rhs) {
	return os << rhs.frequency;
}
