#ifndef BIMAP_H
#define BIMAP_H

#include <unordered_map>

template <typename T, typename U>
class BiMap {
private:
	using size_typeT = typename std::unordered_map<T, U>::size_type;
	using size_typeU = typename std::unordered_map<U, T>::size_type;
	using iterator = typename std::unordered_map<T, U>::iterator;
	using const_iterator = typename std::unordered_map<T, U>::const_iterator;

	std::unordered_map<T, U> mapping;
	std::unordered_map<U, T> reverseMapping;

public:
	/**
	 * @brief Forwards call to count() on the <T, U> map
	 *
	 * @param t The item to count
	 * @return size_typeT The number of occurences
	 */
	size_typeT countT(const T &t) const;

	/**
	 * @brief Forwards call to count() on the <U, T> map
	 *
	 * @param u The item to count
	 * @return size_typeU size_typeT The number of occurences
	 */
	size_typeU countU(const U &u) const;

	/**
	 * @brief Forwards call to at() on the <T, U> map
	 *
	 * @param t The key to search
	 * @return const U& The mapped result
	 */
	const U &atT(const T &t) const;

	/**
	 * @brief Forwards call to at() on the <U, T> map
	 *
	 * @param u The key to search
	 * @return const T& The mapped result
	 */
	const T &atU(const U &u) const;

	/**
	 * @brief Insert a pair of values to the BiMap. Both values should be unique
	 * in their group or the operation fails.
	 *
	 * @param t The first value
	 * @param u The second value
	 * @return true If the operation succeeded
	 * @return false Otherwise
	 */
	bool insert(T t, U u);

	/**
	 * @brief Forwards a call to begin() on the <T, U> map
	 *
	 * @return const_iterator The iterator
	 */
	const_iterator begin() const;

	/**
	 * @brief Forwards a call to end() on the <T, U> map
	 *
	 * @return const_iterator The iterator
	 */
	const_iterator end() const;

	/**
	 * @brief Forwards a call to size() on the <T, U> map
	 *
	 * @return size_typeT The number of elements in the BiMap
	 */
	size_typeT size() const;
};

#include "BiMap.hpp"

#endif
