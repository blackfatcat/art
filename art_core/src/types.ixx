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
}