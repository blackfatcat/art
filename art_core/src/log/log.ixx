module;

export module log;

import core;
import types;

export namespace art {

	namespace log {

		class LogExperience
		{
		public:
			LogExperience();
			~LogExperience();

			void build(core::Gallery& gallery);

			StringView get_name();

		private:

		};
	} // namespace log
} // namespace art