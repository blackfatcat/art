module;

export module log;

import gallery;
import types;

export namespace art {

	namespace log {

		class LogExperience
		{
		public:
			static LogExperience* create() { return new LogExperience{}; }
			static void destroy(void* self) { delete reinterpret_cast<LogExperience*>(self); }
			void build(core::Gallery& gallery);

		private:

		};
	} // namespace log
} // namespace art