module;

#include <SDL3/SDL.h>
#include <flecs.h>

module canvas;

import core;

namespace art {

	namespace canvas {

		void SDLCanvasHnadler::add_canvas(Canvas& canvas)
		{
			SDL_Window* window = SDL_CreateWindow(canvas.name, canvas.width, canvas.height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY);

			if (!window) {
				util::log(std::source_location::current(), "Error Creating widnow with name= {}, width= {}, height= {}. SDL error= {}", canvas.name, canvas.width, canvas.height, SDL_GetError());
				return;
			}

			m_canvases.insert({ canvas.name, window });

			// print some information about the window
			if (!canvas.hidden)
				SDL_ShowWindow(window);

			{
				int width, height, bbwidth, bbheight;
				SDL_GetWindowSize(window, &width, &height);
				SDL_GetWindowSizeInPixels(window, &bbwidth, &bbheight);
				util::log(std::source_location::current(), "Window size: {}x{}", width, height);
				util::log(std::source_location::current(), "Backbuffer size: {}x{}", bbwidth, bbheight);
				if (width != bbwidth) {
					util::log(std::source_location::current(), "This is a highdpi environment.");
				}
			}
		}

		void SDLCanvasHnadler::update_canvas(art::core::ExpoState& expo_state)
		{
			SDL_Event e;
			//Handle events on queue
			while (SDL_PollEvent(&e) != 0)
			{
				//User requests quit
				if (e.type == SDL_EVENT_QUIT)
				{
					expo_state.open = false;
				}
			}
		}

		SDLCanvasHnadler* art::canvas::SDLCanvasHnadler::create()
		{
			return new SDLCanvasHnadler{};
		}

		void SDLCanvasHnadler::build( art::core::Gallery& gallery )
		{
			gallery.GetExpo().entity().add<Canvas>();

			gallery.add_technique<Canvas&>(flecs::OnStart, std::bind(&SDLCanvasHnadler::add_canvas, this, std::placeholders::_1), "add_canvas");
			gallery.add_technique<art::core::ExpoState&>(flecs::OnUpdate, std::bind(&SDLCanvasHnadler::update_canvas, this, std::placeholders::_1), "update_canvas");
		
			//gallery.GetExpo().query_builder< Canvas&, art::core::ExpoState& >().term_at(1).singleton().build().each(std::bind(&SDLCanvasHnadler::update_canvas, this, std::placeholders::_1));
		}

	} // namespace canvas
} // namespace art