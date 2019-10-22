#ifndef PAIR_HASH_H
#define PAIR_HASH_H

#include <utility>

namespace std {
	template <typename X, typename Y>
	struct hash<std::pair<X, Y>> {
		std::size_t operator()(const std::pair<X, Y> &pair) const {
			return std::hash<X>()(pair.first) ^ std::hash<Y>()(pair.second);
		}
	};
} // namespace std

#endif
