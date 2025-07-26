module;

module gallery;

import types;
import util;

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
			util::log("Registered Experiences: ");
			for (const auto& exp_name : m_experiences)
				util::log("{} ", exp_name);

			while (true)
			{
				m_runner.run(m_mainFlow).wait();
			}
		}

	} // namespace core
} // namespace art