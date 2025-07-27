module;

#include <flecs.h>

export module types;

import std;

export {
	template <
		class T,
		class Allocator = std::allocator<T>
	>
	using Vector = std::vector<T, Allocator>;

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

	enum class Piece : int {};
	using Exposition = flecs::world;

	template <class FuncType>
	using Functor = std::function<FuncType>;
}