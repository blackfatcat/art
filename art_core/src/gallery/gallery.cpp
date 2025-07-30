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
			GetExpo().component<ExpoState>().add(flecs::Singleton);
			GetExpo().set<ExpoState>({ true });

			auto start = util::time::now();
			while ( GetExpo().get<ExpoState>().open )
			{
				auto end = util::time::now();
				util::time::Duration<> delta_time = end - start;
				start = util::time::now();

				GetExpo().progress(delta_time.count());
			}

			for (auto& [name, destroyer] : m_destroyers) {
				util::log(std::source_location::current(), "Destorying {}...", name);
				destroyer(m_experiences[name]);
			}

			util::log(std::source_location::current(), "");
		}

	} // namespace core
} // namespace art