#include <SDL.h>
#include <iostream>
#include "game_loop.h"
#include "singletons.h"
#include "enemy.h"

using namespace std;

GameLoop::GameLoop() : BaseSystem("GameLoop") {
	
}

GameLoop::~GameLoop() {
	
}

void GameLoop::Init() throw() {
	
}

void GameLoop::Terminate() {
	
}

void GameLoop::Loop() throw() {
	// Game Loop
	// Input keys
	// Update positions
	// Check colisions
	// Update stats
	// Render
	// sleep(5);
	// Terminating
	keepWalking = true;

	for(loopCount = 0; keepWalking; loopCount++) {
		LoopStart();
		HandleEvents();
		HandleLogic();
		Render();
		LoopEnd();
	}
}

void GameLoop::LoopStart() {
	
	if(loopCount % 500 == 0 && Enemy::objectCount < 10) {
		
		Enemy *enemy = new Enemy();
		enemy->Init();
		Singleton::allEnemies->RegisterObject(enemy);		
	}
}

void GameLoop::HandleEvents() {
	
	SDL_Event event = { 0 };
	
//	if(SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_FIRSTEVENT, SDL_KEYUP) > 0) {
	if(SDL_PollEvent(&event) > 0) {
		
		switch(event.type) {
			
		case SDL_QUIT:
			cout << "quit event" << endl;
			keepWalking = false;
			break;
		case SDL_WINDOWEVENT:
			switch(event.window.event) {
			case SDL_WINDOWEVENT_SHOWN:
				//cout << "SDL_WINDOWEVENT_SHOWN";
				break;
			case SDL_WINDOWEVENT_HIDDEN:
				//cout << "SDL_WINDOWEVENT_HIDDEN";
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				//cout << "SDL_WINDOWEVENT_EXPOSED";
				break;
			case SDL_WINDOWEVENT_MOVED:
				//cout << "SDL_WINDOWEVENT_MOVED";
				break;
			case SDL_WINDOWEVENT_RESIZED:
				//cout << "SDL_WINDOWEVENT_RESIZED";
				break;
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				//cout << "SDL_WINDOWEVENT_SIZE_CHANGED";
				break;
			case SDL_WINDOWEVENT_MINIMIZED:
				//cout << "SDL_WINDOWEVENT_MINIMIZED";
				break;
			case SDL_WINDOWEVENT_MAXIMIZED:
				//cout << "SDL_WINDOWEVENT_MAXIMIZED";
				break;
			case SDL_WINDOWEVENT_RESTORED:
				//cout << "SDL_WINDOWEVENT_RESTORED";
				break;
			case SDL_WINDOWEVENT_ENTER:
				//cout << "SDL_WINDOWEVENT_ENTER";
				break;
			case SDL_WINDOWEVENT_LEAVE:
				//cout << "SDL_WINDOWEVENT_LEAVE";
				break;
			case SDL_WINDOWEVENT_FOCUS_GAINED:
				//cout << "SDL_WINDOWEVENT_FOCUS_GAINED";
				break;
			case SDL_WINDOWEVENT_FOCUS_LOST:
				//cout << "SDL_WINDOWEVENT_FOCUS_LOST";
				break;
			case SDL_WINDOWEVENT_CLOSE:
				cout << "SDL_WINDOWEVENT_CLOSE" << endl;
				keepWalking - false;
				break;
			default:
				cout << "Unknown [" << (int)event.window.event << "]" << endl;
				break;
			}
			break;
		// Keyboard
		case SDL_KEYDOWN:
		case SDL_KEYUP:
//			if(event.type == SDL_KEYDOWN){
//				cout << "down " << event.key.keysym.sym << endl;
//			} else {
//				cout << "up " << event.key.keysym.sym << endl;
//			}
			switch(event.key.keysym.sym) {
			case SDLK_LEFT:
				Singleton::player->CommandSetOrReset(Player::left, event.type == SDL_KEYDOWN);
				break;
			case SDLK_RIGHT:
				Singleton::player->CommandSetOrReset(Player::right, event.type == SDL_KEYDOWN);
				break;
			case SDLK_UP:
				Singleton::player->CommandSetOrReset(Player::up, event.type == SDL_KEYDOWN);
				break;
			case SDLK_DOWN:
				Singleton::player->CommandSetOrReset(Player::down, event.type == SDL_KEYDOWN);
				break;
			case SDLK_ESCAPE:
				keepWalking = false;
				break;
			case SDLK_SPACE:
				Singleton::player->CommandSetOrReset(Player::fire, event.type == SDL_KEYDOWN);
				break;
			}
			break;
		case SDL_TEXTEDITING:
			break;
		case SDL_TEXTINPUT:
			break;
		// Mouse
		case SDL_MOUSEMOTION:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		case SDL_MOUSEBUTTONUP:
			break;
		case SDL_MOUSEWHEEL:
			break;
		// Touch
		case SDL_FINGERDOWN:
		case SDL_FINGERUP:
		case SDL_FINGERMOTION:
			break;
		default:
			cout << "event type:" << "0x" << hex << event.type << endl;
			break;
		}
	}	
}

void GameLoop::HandleLogic() {
	
	Singleton::player->HandleLogic();
	Singleton::allFriends->HandleLogic();
	Singleton::allEnemies->HandleLogic();
	return;
}

void GameLoop::Render() {

	SDL_SetRenderDrawColor(Singleton::screen->renderer, 0, 0, 0, 0);
	SDL_RenderClear(Singleton::screen->renderer);
	
	Singleton::allEnemies->Render();
	Singleton::allFriends->Render();
	Singleton::player->Render();
//	Singleton::player->PrintStates();
	
	SDL_RenderPresent(Singleton::screen->renderer);
}

void GameLoop::LoopEnd() {
	
}
