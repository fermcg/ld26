#include <SDL.h>
#include <iostream>

#include "game_system.h"
#include "exceptions.h"
#include "macros.h"

using namespace std;

GameSystem::GameSystem() : BaseSystem("GameSystem") {
	
}
GameSystem::~GameSystem() {
	
}
void GameSystem::Init() throw() {
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		
		cerr << "SDL_Init error: " << SDL_GetError() << endl;
		THROW(Exception::InitializationFailure);
	}

	this->BaseSystem::Init();
}
void GameSystem::Terminate() {
	
	SDL_Quit();
	this->BaseSystem::Terminate();
}