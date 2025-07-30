module;

#include <SDL3/SDL.h>
#include <flecs.h>

export module canvas;

import core;

export namespace art {
	
	namespace canvas {

		struct CanvasComp
		{
			CanvasComp() {}
			const char* name = "window";
			int16_t width = 1920;
			int16_t height = 1080;
			bool hidden = false;
		};

		class SDLCanvasExp
		{
		public:
			SDLCanvasExp();
			~SDLCanvasExp();

			void add_canvas(CanvasComp& canvas);

			void build( art::core::Gallery& gallery );

		private:
			HashMap<StringView, SDL_Window*> m_canvases;
		};
	} // namespace canvas
} // namespace art