#include <iostream>

#include "screen.h"
#include "singletons.h"
#include "exceptions.h"
#include "macros.h"

using namespace std;

Screen::Screen() : BaseSystem("Screen") {

	window = NULL;
	renderer = NULL;
}
Screen::~Screen() {

}
void Screen::Init() throw() {

	const char* gameTitle = "Pato Loco";
	const char* windowSection = "WINDOW";

	int width = 0;
	int height = 0;

	Singleton::config->Read(windowSection, "width", width, 640);
	Singleton::config->Read(windowSection, "height", height, 480);

	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	// | SDL_WINDOW_FULLSCREEN;

	window = SDL_CreateWindow(gameTitle, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height, flags);
	if (window == NULL) {

		cerr << "SDL_CreateWindow error: " << SDL_GetError() << endl;
		THROW(Exception::InitializationFailure);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {

		cerr << "SDL_CreateRenderer error: " << SDL_GetError() << endl;
		THROW(Exception::InitializationFailure);
	}
	this->BaseSystem::Init();	
}
void Screen::Terminate() {

	if (renderer != NULL) {

		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}

	if (window != NULL) {

		SDL_DestroyWindow(window);
		window = NULL;
	}

	this->BaseSystem::Terminate();
}
