module;

#include "taskflow/taskflow.hpp";
#include "entt/entt.hpp";

export module paint;

import std;
import core;

export namespace art {
	
	namespace paint {

		class Painter
		{
		public:
			Painter();
			~Painter();

			void build( art::core::Gallery& gallery );

		private:
			tf::Taskflow m_ArtFlow;
		};


	} // namespace paint
} // namespace art