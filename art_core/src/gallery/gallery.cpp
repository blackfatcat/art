module;

#include <flecs.h>

module gallery;

import types;
import util;

namespace art {

	namespace core {

		Gallery::Gallery() : m_exposition()
		{
		}

		Gallery::~Gallery()
		{
		}

		void Gallery::showtife()
		{
			while (true)
			{
				m_runner.run(m_mainFlow).wait();
			}
		}

	} // namespace core
} // namespace art