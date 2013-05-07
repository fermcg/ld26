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

	this->BaseSystem::Init();
}
void GameSystem::Terminate() {

	this->BaseSystem::Terminate();
}
