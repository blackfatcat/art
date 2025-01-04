module;

export module types;

import std;

export {
	using StringView = std::string_view;

	template <
		class T,
		class HashFn = std::hash<T>,
		class TCompare = std::equal_to<T>,
		class Allocator = std::allocator<T>
	>
	using HashSet = std::unordered_set<T, HashFn, TCompare, Allocator>;

	template <
		class Key,
		class Value,
		class KeyHashFn = std::hash<Key>,
		class KeyCompare = std::equal_to<Key>,
		class Allocator = std::allocator<std::pair<const Key, Value>>
	>
	using HashMap = std::unordered_map<Key, Value, KeyHashFn, KeyCompare, Allocator>;
}