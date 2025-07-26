module;

#include "taskflow/taskflow.hpp"
#include "entt/entt.hpp"

export module canvas;

import std;
import core;

export namespace art {
	
	namespace canvas {

		class Canvas
		{
		public:
			Canvas();
			~Canvas();

			void build( art::core::Gallery& gallery );

		private:
		};


	} // namespace canvas
} // namespace art