module;

module core;

import types;

namespace art {

	namespace core {

		Gallery::Gallery()
		{
		}

		Gallery::~Gallery()
		{
		}

		void Gallery::showtife()
		{
			std::print("Registered Experiences: ");
			for (const auto& exp_name : m_experiences)
				std::print("{} ", exp_name);
			std::println("");

			while (true)
			{
				m_runner.run(m_mainFlow).wait();
			}
		}

	} // namespace core
} // namespace art