#ifndef HUFFMAN_ENCODER_DECODER
#define HUFFMAN_ENCODER_DECODER

#include <bits/stdc++.h>
#include "EncoderDecoder/AbstractEncoderDecoder.h"
#include "EncoderDecoder/Huffman/PaddedString.h"
#include "BiMap/BiMap.h"

class HuffmanEncoderDecoder : public AbstractEncoderDecoder<
	BiMap<char, std::pair<unsigned char, unsigned int>>, PaddedString> {
private:
	class Node {
	public:
		char character;
		int frequency;
		std::unique_ptr<Node> leftSon;
		std::unique_ptr<Node> rightSon;

		Node();
		Node(char c);
		Node(Node &&rhs) = default;
		Node &operator=(Node &&rhs) = default;
		bool operator==(const Node &rhs) const;
		Node &operator++(int);
	};

public:
	using MappingType = BiMap<char, std::pair<unsigned char, unsigned int>>;
	using EncodedType = PaddedString;
	using NodePtr = std::unique_ptr<Node>;
	using NodeVector = std::vector<NodePtr>;
	friend class HuffmanEncoderDecoder_makeEncodingFromTextSubRoutines_Test;

private:
	static const MappingType canonicalMapping;

	bool usingCanonicalEncoding;
	MappingType mapping;

	/**
	 * @brief Calculate the frequency (number of occurences) of each character in a string
	 *
	 * @param plaintext The input string
	 * @return NodeVector A vector with exactly 256 elements (1 per char value) that
	 * contains Nodes with the corresponding chars and their frequencies
	 */
	static NodeVector getFrequencies(const std::string &plaintext);

	/**
	 * @brief Create a prefixless binary tree of Nodes given a vector with the corresponding
	 * frequencies for each character
	 *
	 * @param frequencies The Node vector
	 * @return NodePtr& The root of the tree
	 */
	static NodePtr buildPrefixlessTree(NodeVector &frequencies);

	/**
	 * @brief Convert a prefixless binary tree into a huffman mapping
	 *
	 * @param root The root of the tree
	 * @return MappingType The huffman mapping
	 */
	static MappingType createMapping(const NodePtr &root);

	/**
	 * @brief A helper function to createMapping. Walks recursively on a tree, building the code and
	 * adding it to the mapping for each leaf node it encounters.
	 *
	 * @param mapping The mapping to populate
	 * @param n The current node we are looking at
	 * @param code The current code
	 */
	static void dfs(MappingType &mapping, const NodePtr &n,
		std::pair<unsigned char, unsigned int> code);

public:
	friend std::ostream &operator<<(std::ostream &os, const Node &);
	friend NodePtr operator+(NodePtr &n1, NodePtr &n2);
};

#endif
