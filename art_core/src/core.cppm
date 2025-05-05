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
			std::println("Registered Experiences: ");
			for (const auto& exp_name : m_experiences)
				std::println("{} ", exp_name);

			while (true)
			{
				m_runner.run(m_mainFlow).wait();
			}
		}

	} // namespace core
} // namespace art