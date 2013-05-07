#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

#include "game_system.h"
#include "exceptions.h"
#include "macros.h"

using namespace std;

const int GameSystem::MaxMixChannels = 16;

GameSystem::GameSystem() : BaseSystem("GameSystem") {

}
GameSystem::~GameSystem() {

}
void GameSystem::Init() throw() {

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {

		cerr << "SDL_Init error: " << SDL_GetError() << endl;
		THROW(Exception::InitializationFailure);
	}

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) != 0) {

		cerr << "Mix_OpenAudio error: " << Mix_GetError() << endl;
		THROW(Exception::InitializationFailure);
	}
	Mix_AllocateChannels(GameSystem::MaxMixChannels);
	this->BaseSystem::Init();
}
void GameSystem::Terminate() {

	SDL_Quit();
	this->BaseSystem::Terminate();
}
