module;

export module util;

import std;
import types;

export namespace util {
	// TODO: Move to time module
	namespace time {
		auto now = std::chrono::high_resolution_clock::now;

		template<typename Period = std::milli>
		using Duration = std::chrono::duration<float, Period>;
	}

	template<typename... Args>
	void log(std::source_location caller, StringView fmt, Args&&... args) {
		std::string msg = std::vformat(fmt, std::make_format_args(args...));
		std::print("\x1B[32mINFO\033[0m\t: {} at Line: {}: ", caller.file_name(), caller.line());
		std::cout << msg << std::endl << std::endl;
	}

	template<typename... Args>
	void error(std::source_location caller, StringView fmt, Args&&... args) {
		std::string msg = std::vformat(fmt, std::make_format_args(args...));
		std::print("\x1B[31mERROR\033[0m\t: {} at Line: {}: ", caller.file_name(), caller.line());
		std::cout << msg << std::endl << std::endl;
	}

	class Defer {
	public:
		explicit Defer(Functor<void()> fn) : func(std::move(fn)) {}
		~Defer() { func(); }

	private:
		Functor<void()> func;
	};

	Defer profile(Functor<void(time::Duration<>)> callback) {
		const auto start = time::now();
		return Defer([start, callback] {
			const auto end = time::now();
			time::Duration<> diff = end - start;

			callback(diff);
		});
	}
}