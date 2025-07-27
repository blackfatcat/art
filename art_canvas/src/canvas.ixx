module;

#include <SDL3/SDL.h>

export module canvas;

import core;

export namespace art {
	
	namespace canvas {

		class Canvas
		{
		public:
			Canvas();
			~Canvas();

			void add_window(StringView name, int16_t width, int16_t height, bool hidden = false);

			void build( art::core::Gallery& gallery );

		private:
			Vector<SDL_Window*> m_windows;
			
		};
	} // namespace canvas
} // namespace art