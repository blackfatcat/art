module;

#include <SDL3/SDL.h>
#include <flecs.h>

export module canvas;

import core;

export namespace art {
	
	namespace canvas {

		struct Canvas
		{
			Canvas() {}
			const char* name = "window";
			int16_t width = 1920;
			int16_t height = 1080;
			bool hidden = false;
		};

		class SDLCanvasHnadler
		{
		public:
			void add_canvas(Canvas& canvas);
			void update_canvas(art::core::ExpoState& expo_state);

			static SDLCanvasHnadler* create();
			static void destroy(void* self) { delete reinterpret_cast<SDLCanvasHnadler*>(self); }
			void build( art::core::Gallery& gallery );

		private:
			HashMap<StringView, SDL_Window*> m_canvases;
		};
	} // namespace canvas
} // namespace art