#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

HuffmanEncoderDecoder::Node::Node() : Node(0) {}

HuffmanEncoderDecoder::Node::Node(char c) :
	character(c), frequency(0), leftSon(nullptr), rightSon(nullptr) {}

bool HuffmanEncoderDecoder::Node::operator==(const Node &rhs) const {
	return (this->character == rhs.character) && (this->frequency == rhs.frequency);
}

HuffmanEncoderDecoder::Node &HuffmanEncoderDecoder::Node::operator++(int) {
	this->frequency++;
	return *this;
}

bool HuffmanEncoderDecoder::Node::operator<(const Node &rhs) const {
	return this->frequency < rhs.frequency;
}

std::ostream &operator<<(std::ostream &os, const HuffmanEncoderDecoder::Node &rhs) {
	return os << rhs.frequency;
}
