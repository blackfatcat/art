module;

module log;

import core;

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
			gallery.add_technique([]() {/*std::println("Woop from Log:)");*/ }, "log_1");
		}
	} // namespace log
} // namespace art