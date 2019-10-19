#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

HuffmanEncoderDecoder::Node::Node() : Node(0) {}

HuffmanEncoderDecoder::Node::Node(char c) :
	character(c), frequency(0), leftSon(nullptr), rightSon(nullptr) {}

bool HuffmanEncoderDecoder::Node::operator==(const Node &rhs) const {
	return (this->character == rhs.character) &&
		(this->frequency == rhs.frequency);
}

HuffmanEncoderDecoder::Node &HuffmanEncoderDecoder::Node::operator++(int) {
	this->frequency++;
	return *this;
}

HuffmanEncoderDecoder::NodePtr operator+(
	HuffmanEncoderDecoder::NodePtr &n1, HuffmanEncoderDecoder::NodePtr &n2) {

	auto result = std::make_unique<HuffmanEncoderDecoder::Node>();
	result->frequency = n1->frequency + n2->frequency;
	result->leftSon = std::move(n1);
	result->rightSon = std::move(n2);
	return result;
}

std::ostream &operator<<(
	std::ostream &os, const HuffmanEncoderDecoder::Node &rhs) {
	return os << rhs.frequency;
}
