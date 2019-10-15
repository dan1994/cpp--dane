#include <numeric>
#include <vector>
#include <algorithm>
#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

const HuffmanEncoderDecoder::MappingType HuffmanEncoderDecoder::canonicalMapping;

HuffmanEncoderDecoder::NodeVector HuffmanEncoderDecoder::getFrequencies(const std::string &plaintext) {

	// Initialize frequencies
	NodeVector frequencies;
	frequencies.reserve(256);
	std::generate(frequencies.begin(), frequencies.begin() + 256, []() {
		static char c = 0;
		return std::make_unique<Node>(Node(c++));
	});

	// Count frequency of each char in plaintext
	std::for_each(plaintext.cbegin(), plaintext.cend(), [&](auto c) {
		auto &fp = frequencies[c];
		(*fp)++;
	});

	return frequencies;
}

HuffmanEncoderDecoder::NodePtr HuffmanEncoderDecoder::buildPrefixlessTree(NodeVector &frequencies) {

	// Sort by ascending order of frequency
	std::sort(frequencies.begin(), frequencies.end(), [](const NodePtr &n1, const NodePtr &n2)
		{ return n1->frequency < n2->frequency; });

	// Find the first element with non-zero frequency
	auto activeSymbols = std::upper_bound(frequencies.begin(), frequencies.end(), 0,
		[](int value, NodePtr &n) { return n->frequency < value; });

	// Copy to list non-zero frequency elements
	std::list<NodePtr> frequenciesList;
	std::copy(std::make_move_iterator(activeSymbols), std::make_move_iterator(frequencies.end()),
		frequenciesList.begin());

	// If there are no elements, return an empty node
	if(frequenciesList.empty()) {
		return nullptr;
	}

	// While there is more than one element in the list
	while(frequenciesList.size() > 1) {
		// Pop first 2 elements
		auto n1 = std::move(frequenciesList.front()); frequenciesList.pop_front();
		auto n2 = std::move(frequenciesList.front()); frequenciesList.pop_front();
		// Create a new one which is their sum
		auto newNode = n1 + n2;
		// Insert it to the correct location in the list
		auto newLoc = std::upper_bound(frequenciesList.begin(), frequenciesList.end(),
			newNode->frequency, [](int frequency, NodePtr &n) { return n->frequency < frequency; });
		frequenciesList.insert(newLoc, std::move(newNode));
	}

	return std::move(frequenciesList.front());
}
