#include "BiMap.h"

template <typename T, typename U>
typename std::unordered_map<T, U>::size_type BiMap<T, U>::countT(
	const T &t) const {
	return this->mapping.count(t);
}

template <typename T, typename U>
typename std::unordered_map<U, T>::size_type BiMap<T, U>::countU(
	const U &u) const {
	return this->reverseMapping.count(u);
}

template <typename T, typename U>
const U &BiMap<T, U>::atT(const T &t) const {
	return this->mapping.at(t);
}

template <typename T, typename U>
const T &BiMap<T, U>::atU(const U &u) const {
	return this->reverseMapping.at(u);
}

template <typename T, typename U>
bool BiMap<T, U>::insert(T t, U u) {
	if(this->mapping.count(t) > 0 || this->reverseMapping.count(u) > 0) {
		return false;
	}

	auto [it1, success1] = this->mapping.insert(std::pair<T, U>(t, u));
	if(!success1) {
		return false;
	}

	auto [it2, success2] = this->reverseMapping.insert(std::pair<U, T>(u, t));
	if(!success2) {
		this->mapping.erase(it1);
		return false;
	}

	return true;
}

template <typename T, typename U>
typename BiMap<T, U>::const_iterator BiMap<T, U>::begin() const {
	return this->mapping.begin();
}

template <typename T, typename U>
typename BiMap<T, U>::const_iterator BiMap<T, U>::end() const {
	return this->mapping.end();
}

template <typename T, typename U>
typename BiMap<T, U>::size_typeT BiMap<T, U>::size() const {
	return this->mapping.size();
}
