module;

module canvas;

import std;
import types;
import core;

namespace art {

	namespace canvas {

		Canvas::Canvas()
		{
		}

		Canvas::~Canvas()
		{
		}

		void Canvas::build( art::core::Gallery& gallery )
		{
			gallery.add_technique([]() {}, "canvas_1");
		}

	} // namespace canvas
} // namespace art