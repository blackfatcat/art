module;

module paint;

import std;
import types;
import core;

namespace art {

	namespace paint {

		Painter::Painter()
		{
		}

		Painter::~Painter()
		{
		}

		void Painter::build( art::core::Gallery& gallery )
		{
			gallery.add_technique([]() {}, "painter_1");
		}

	} // namespace paint
} // namespace art