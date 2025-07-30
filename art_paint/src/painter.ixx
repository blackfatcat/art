module;

export module paint;

import core;

export namespace art {
	
	namespace paint {

		class Painter
		{
		public:
			static Painter* create() { return new Painter{}; }
			static void destroy(void* self) { delete reinterpret_cast<Painter*>(self); }

			void build( art::core::Gallery& gallery );

		private:
		};


	} // namespace paint
} // namespace art