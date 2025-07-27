module;

#include <SDL3/SDL.h>

module canvas;

import core;

namespace art {

	namespace canvas {

		Canvas::Canvas()
		{
		}

		Canvas::~Canvas()
		{
		}

		void Canvas::add_window(StringView name, int16_t width, int16_t height, bool hidden)
		{
			SDL_Window* window = SDL_CreateWindow(name.data(), width, height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);
			m_windows.push_back(window);

			if (!window) {
				util::log("Error Creating widnow with name= {}, width= {}, height= {}. SDL error= {}", name, width, height, SDL_GetError());
			}

			// print some information about the window
			if (!hidden) 
				SDL_ShowWindow(window);

			{
				int width, height, bbwidth, bbheight;
				SDL_GetWindowSize(window, &width, &height);
				SDL_GetWindowSizeInPixels(window, &bbwidth, &bbheight);
				util::log("Window size: {}x{}}", width, height);
				util::log("Backbuffer size: {}x{}", bbwidth, bbheight);
				if (width != bbwidth) {
					util::log("This is a highdpi environment.");
				}
			}
		}

		void Canvas::build( art::core::Gallery& gallery )
		{
			gallery.add_technique([]() {}, "canvas_1");
		}

	} // namespace canvas
} // namespace art