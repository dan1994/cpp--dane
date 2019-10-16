#include <numeric>
#include <vector>
#include <algorithm>
#include "Pair/Hash.h"
#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

const HuffmanEncoderDecoder::MappingType HuffmanEncoderDecoder::canonicalMapping;

HuffmanEncoderDecoder::NodeVector HuffmanEncoderDecoder::getFrequencies(const std::string &plaintext) {

	// Initialize frequencies
	NodeVector frequencies;
	frequencies.reserve(256);
	for(int c = 0; c < 256; c++) {
		frequencies.push_back(std::make_unique<Node>(Node(c)));
	}

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
		[](int value, NodePtr &n) { return n->frequency > value; });

	// Copy to list non-zero frequency elements
	std::list<NodePtr> frequenciesList;
	std::copy(std::make_move_iterator(activeSymbols), std::make_move_iterator(frequencies.end()),
		std::back_inserter(frequenciesList));

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
			newNode->frequency, [](int frequency, NodePtr &n) { return n->frequency > frequency; });
		frequenciesList.insert(newLoc, std::move(newNode));
	}

	return std::move(frequenciesList.front());
}

HuffmanEncoderDecoder::MappingType HuffmanEncoderDecoder::createMapping(const NodePtr &root) {
	MappingType mapping;

	// If the tree is empty, then so should the mapping be
	if(root == nullptr) {
		return mapping;
	}

	// If the tree has only one element, we want to assign it a single-bit 0 code
	if(root->leftSon == nullptr && root->rightSon == nullptr) {
		mapping.insert(root->character, std::make_pair<unsigned char, unsigned int>(1, 0));
		return mapping;
	}

	// Otherwise we use dfs on the tree with an initial code of 0 length
	HuffmanEncoderDecoder::dfs(mapping, root, std::make_pair<unsigned char, unsigned int>(0, 0));
	return mapping;
}

void HuffmanEncoderDecoder::dfs(MappingType &mapping, const NodePtr &n,
	std::pair<unsigned char, unsigned int> code) {

	// We reached a leaf node, so we insert it to the mapping
	if(n->leftSon == nullptr && n->rightSon == nullptr) {
		mapping.insert(n->character, code);
		return;
	}

	// If we have a left son, we concatenate a 0 to the code, and recurse
	if(n->leftSon != nullptr) {
		code.first++;
		code.second *= 2;
		dfs(mapping, n->leftSon, code);
		code.first--;
		code.second /= 2;
	}

	// If we have a left son, we concatenate a 1 to the code, and recurse
	if(n->rightSon != nullptr) {
		code.first++;
		code.second = (2 * code.second) + 1;
		dfs(mapping, n->rightSon, code);
		code.first--;
		code.second = (code.second - 1) / 2;
	}
}
