module;

module log;

import core;
import std;

namespace art {
	namespace log {

		LogExperience::LogExperience()
		{
		}

		LogExperience::~LogExperience()
		{
		}

		void LogExperience::build(art::core::Gallery& gallery)
		{
			std::println("built logging plugin:)");
			gallery.add_technique([]() { }, "log_1");
		}
	} // namespace log
} // namespace art