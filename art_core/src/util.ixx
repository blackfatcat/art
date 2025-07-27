module;

export module util;

import std;
import <ratio>;
import <chrono>;
import types;

export namespace util {
	template<typename... Args>
	void log(StringView fmt, Args&&... args) {
		std::string msg = std::vformat(fmt, std::make_format_args(args...));
		std::cout << msg << std::endl;
	}

	class Defer {
	public:
		explicit Defer(Functor<void()> fn) : func(std::move(fn)) {}
		~Defer() { func(); }

	private:
		Functor<void()> func;
	};

	Defer profile(Functor<void(std::chrono::duration<double, std::milli>)> callback) {
		const auto start = std::chrono::high_resolution_clock::now();
		return Defer([start, callback] {
			const auto end = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> diff = end - start;

			callback(diff);
		});
	}
}