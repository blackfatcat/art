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
			auto start = util::time::now();
			while (true)
			{
				auto end = util::time::now();
				float delta_time = (end - start).count();
				start = util::time::now();

				GetExpo().progress(delta_time);
			}
		}

	} // namespace core
} // namespace art