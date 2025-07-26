module;

export module util;

import std;
import types;

export namespace util {
	template<typename... Args>
	void log(StringView fmt, Args&&... args) {
		std::string msg = std::vformat(fmt, std::make_format_args(args...));
		std::cout << msg << std::endl;
	}
}