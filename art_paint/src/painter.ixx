module;

#include <taskflow/taskflow.hpp>

export module paint;

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