#pragma once

#include <SDL.h>
#include "base_system.h"

class Screen : public BaseSystem {
	public:
		Screen();
		~Screen();

		void Init() throw();
		void Terminate();

		void ToogleFullScreen();

		SDL_Window* window;	
		SDL_Renderer* renderer;

	private:

		bool fullScreen;
};
