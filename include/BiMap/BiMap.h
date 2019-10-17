#ifndef BIMAP_H
#define BIMAP_H

#include <unordered_map>

template <typename T, typename U>
class BiMap {
private:
	std::unordered_map<T, U> mapping;
	std::unordered_map<U, T> reverseMapping;

public:
	typename std::unordered_map<T, U>::size_type countT(const T &t) const;
	typename std::unordered_map<U, T>::size_type countU(const U &u) const;
	const U &atT(const T &t) const;
	const T &atU(const U &u) const;
	bool insert(T t, U u);
};

#include "BiMap.hpp"

#endif
