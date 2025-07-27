module paint;

import core;

namespace art {

	namespace paint {

		Painter::Painter() {}
		Painter::~Painter() {}

		void Painter::build(art::core::Gallery& gallery) {
			gallery.add_technique([]() {}, "painter");
		}

	} // namespace paint
} // namespace art