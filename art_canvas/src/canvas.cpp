module;

#include <SDL3/SDL.h>
#include <flecs.h>

module canvas;

import core;

namespace art {

	namespace canvas {

		SDLCanvasExp::SDLCanvasExp()
		{
		}

		SDLCanvasExp::~SDLCanvasExp()
		{
		}

		void SDLCanvasExp::add_canvas(CanvasComp& canvas)
		{
			SDL_Window* window = SDL_CreateWindow(canvas.name, canvas.width, canvas.height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

			if (!window) {
				util::log("Error Creating widnow with name= {}, width= {}, height= {}. SDL error= {}", canvas.name, canvas.width, canvas.height, SDL_GetError());
				return;
			}

			//m_canvases.insert({ canvas.name, window });

			// print some information about the window
			if (!canvas.hidden)
				SDL_ShowWindow(window);

			{
				int width, height, bbwidth, bbheight;
				SDL_GetWindowSize(window, &width, &height);
				SDL_GetWindowSizeInPixels(window, &bbwidth, &bbheight);
				util::log("Window size: {}x{}", width, height);
				util::log("Backbuffer size: {}x{}", bbwidth, bbheight);
				if (width != bbwidth) {
					util::log("This is a highdpi environment.");
				}
			}
		}

		void SDLCanvasExp::build( art::core::Gallery& gallery )
		{
			gallery.GetExpo().entity().add<CanvasComp>();
			gallery.add_technique<CanvasComp&>(flecs::OnStart, std::bind(&SDLCanvasExp::add_canvas, this, std::placeholders::_1), "add_canvas");
		}

	} // namespace canvas
} // namespace art