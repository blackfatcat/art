module;

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
		};


	} // namespace paint
} // namespace art