#include "EncoderDecoder/Huffman/HuffmanEncoderDecoder.h"

HuffmanEncoderDecoder::NodeVector HuffmanEncoderDecoder::getFrequencies(
	const std::string &plaintext) {

	// Initialize frequencies
	NodeVector frequencies;
	constexpr auto size = std::numeric_limits<unsigned char>::max() + 1;
	frequencies.reserve(size);
	for(int c = 0; c < size; c++) {
		frequencies.push_back(std::make_unique<Node>(Node(c)));
	}

	// Count frequency of each char in plaintext
	std::for_each(plaintext.cbegin(), plaintext.cend(), [&](unsigned char c) {
		auto &fp = frequencies[c];
		(*fp)++;
	});

	return frequencies;
}

HuffmanEncoderDecoder::NodePtr HuffmanEncoderDecoder::buildPrefixlessTree(
	NodeVector &frequencies) {

	// Sort by ascending order of frequency
	std::sort(frequencies.begin(),
		frequencies.end(),
		[](const NodePtr &n1, const NodePtr &n2) {
			return n1->frequency < n2->frequency;
		});

	// Find the first element with non-zero frequency
	auto activeSymbols = std::upper_bound(
		frequencies.begin(), frequencies.end(), 0, [](int value, NodePtr &n) {
			return n->frequency > value;
		});

	// Copy to list non-zero frequency elements
	std::list<NodePtr> frequenciesList;
	std::move(
		activeSymbols, frequencies.end(), std::back_inserter(frequenciesList));

	// If there are no elements, return an empty node
	if(frequenciesList.empty()) {
		return nullptr;
	}

	// Build a tree out of the list elements
	while(frequenciesList.size() > 1) {
		// Pop first 2 elements
		auto n1 = std::move(frequenciesList.front());
		frequenciesList.pop_front();
		auto n2 = std::move(frequenciesList.front());
		frequenciesList.pop_front();
		// Create a new one which is their sum
		auto newNode = n1 + n2;
		// Insert it to the correct location in the list
		auto newLoc = std::upper_bound(frequenciesList.begin(),
			frequenciesList.end(),
			newNode->frequency,
			[](int frequency, NodePtr &n) { return n->frequency > frequency; });
		frequenciesList.insert(newLoc, std::move(newNode));
	}

	return std::move(frequenciesList.front());
}

HuffmanEncoderDecoder::MappingType HuffmanEncoderDecoder::createMapping(
	const NodePtr root) {

	MappingType mapping;

	// If the tree is empty, then so should the mapping be
	if(root == nullptr) {
		return mapping;
	}

	// If the tree has only one element, we want to assign it a single-bit 0
	// code
	if(root->leftSon == nullptr && root->rightSon == nullptr) {
		mapping.insert(
			root->character, std::make_pair<unsigned char, unsigned int>(1, 0));
		return mapping;
	}

	// Otherwise we use dfs on the tree with an initial code of 0 length
	HuffmanEncoderDecoder::dfs(mapping,
		root,
		std::make_pair<unsigned char, unsigned int>(0, 0),
		std::numeric_limits<unsigned int>::digits);

	return mapping;
}

void HuffmanEncoderDecoder::dfs(MappingType &mapping,
	const NodePtr &n,
	std::pair<unsigned char, unsigned int> code,
	int depth) {

	// We reached a leaf node, so we insert it to the mapping
	if(n->leftSon == nullptr && n->rightSon == nullptr) {
		mapping.insert(n->character, code);
		return;
	}

	// If depth is 0, than we won't have enough space to represent certain
	// characters
	if(depth == 0) {
		throw std::length_error(
			"The tree depth is more than the max representation length");
	}

	// If we have a left son, we concatenate a 0 to the code, and recurse
	if(n->leftSon != nullptr) {
		code.first++;
		code.second *= 2;
		dfs(mapping, n->leftSon, code, depth - 1);
		code.first--;
		code.second /= 2;
	}

	// If we have a left son, we concatenate a 1 to the code, and recurse
	if(n->rightSon != nullptr) {
		code.first++;
		code.second = (2 * code.second) + 1;
		dfs(mapping, n->rightSon, code, depth - 1);
		code.first--;
		code.second = (code.second - 1) / 2;
	}
}

HuffmanEncoderDecoder::EncodedType HuffmanEncoderDecoder::encode(
	const std::string &plaintext) const {

	constexpr unsigned char BITS_IN_CHAR =
		std::numeric_limits<unsigned char>::digits;

	// Convert the characters into encoded symbols with the mapping
	std::vector<std::pair<unsigned char, unsigned int>> encodedSymbols;
	std::transform(plaintext.begin(),
		plaintext.end(),
		std::back_inserter(encodedSymbols),
		[&m = this->mapping](auto c) {
			try {
				return std::pair(m.atT(c));
			} catch(std::out_of_range &) {
				std::string msg =
					"There is no encoded symbol corresponding to char ";
				msg += c;
				throw std::out_of_range(msg);
			}
		});

	EncodedType encodedText;
	unsigned char currentSize = 0;
	char currentChar = 0;

	for(auto [encodedSize, encodedValue] : encodedSymbols) {
		while(encodedSize > 0) {
			// We can each time insert the min of what is left of the current
			// symbol and the space remaining in currentChar
			auto sizeToInsert = std::min(encodedSize,
				static_cast<unsigned char>(BITS_IN_CHAR - currentSize));
			currentChar = currentChar << sizeToInsert |
				encodedValue >> (encodedSize - sizeToInsert);
			currentSize += sizeToInsert;
			encodedSize -= sizeToInsert;
			// When the char is full, append it to the string and reset the
			// state
			if(currentSize == BITS_IN_CHAR) {
				encodedText.s += currentChar;
				currentChar = 0;
				currentSize = 0;
			}
		}
	}

	// We may have leftovers so we calculate the padding encodedSize, add the
	// padding and the last char
	encodedText.paddingSize =
		(currentSize == 0) ? 0 : BITS_IN_CHAR - currentSize;
	if(encodedText.paddingSize > 0) {
		currentChar <<= encodedText.paddingSize;
		encodedText.s += currentChar;
	}

	return encodedText;
}

std::string HuffmanEncoderDecoder::decode(
	const HuffmanEncoderDecoder::EncodedType &encodedText) const {

	constexpr unsigned char BITS_IN_CHAR =
		std::numeric_limits<unsigned char>::digits;

	std::string plaintext;
	auto charIt = encodedText.s.begin();
	unsigned char offsetInChar = BITS_IN_CHAR;
	unsigned char currentLength = 0;
	unsigned int currentValue = 0;

	// Go over all chars
	auto lastCharIt = --encodedText.s.end();
	while(charIt != lastCharIt || offsetInChar > encodedText.paddingSize) {
		// Decoding error: The length of the current "guess" is larger than the
		// max length
		if(currentLength == std::numeric_limits<unsigned int>::digits) {
			throw std::length_error("Exceeded the maximum length of an encoded "
									"character w/o finding a decodable result");
		}

		// Append a bit to the current value
		offsetInChar--;
		currentValue = (currentValue << 1) | ((*charIt >> offsetInChar) & 1);
		currentLength++;

		// If we finished going over the current char, go to the next
		if(offsetInChar == 0) {
			charIt++;
			offsetInChar = BITS_IN_CHAR;
		}

		// Try adding the character corresponding to the current encoding
		// If it doesn't exist, atU will throw an exception, and we'll try again
		// next time
		try {
			plaintext += this->mapping.atU({currentLength, currentValue});
			currentValue = 0;
			currentLength = 0;
		} catch(std::out_of_range &) {}
	}

	// Decoding error: Reached padding in the middle of symbol
	if(currentLength != 0) {
		throw std::out_of_range(
			"Reached end of encoded input in the middle of decoding");
	}

	return plaintext;
}

void HuffmanEncoderDecoder::makeEncodingFromText(const std::string &plaintext) {
	auto frequencies = HuffmanEncoderDecoder::getFrequencies(plaintext);
	auto root = HuffmanEncoderDecoder::buildPrefixlessTree(frequencies);
	// This might throw an exception that should be passed to the caller
	this->mapping = HuffmanEncoderDecoder::createMapping(std::move(root));
}

void HuffmanEncoderDecoder::setEncoding(MappingType mapping) {
	this->mapping = std::move(mapping);
}

const HuffmanEncoderDecoder::MappingType &
	HuffmanEncoderDecoder::getEncoding() const {

	return this->mapping;
}
