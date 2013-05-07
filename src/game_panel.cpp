#include "game_panel.h"
#include "singletons.h"

GamePanel::GamePanel() : BaseSystem("GamePanel") {
}

GamePanel::~GamePanel() {
}

void GamePanel::Init() {

	this->BaseSystem::Init();

	greenBar = Singleton::spriteMap->Get("ENERGY+G");
	redBar = Singleton::spriteMap->Get("ENERGY+R");

	redNumbers = Singleton::spriteMap->Get("NUMBERS+R");
	greenNumbers = Singleton::spriteMap->Get("NUMBERS+G");
	blueNumbers = Singleton::spriteMap->Get("NUMBERS+B");

	energyBarRect.x = 640 / 2 - (greenBar->rect.w + 48) / 2;
	energyBarRect.y = 20;
	energyBarRect.w = 80;
	energyBarRect.h = 4;

	powerUpsRect.x = energyBarRect.x + energyBarRect.w + 16;
	powerUpsRect.y = energyBarRect.y;
	powerUpsRect.w = 8;
	powerUpsRect.h = 8;

}

void GamePanel::Terminate() {

	this->BaseSystem::Terminate();
}

void GamePanel::Render() {

	ShowEnergyBar();
	ShowPowerUps();
}

void GamePanel::ShowEnergyBar() {

	SDL_Rect redRect = energyBarRect;
	redBar->RenderCopy(&redRect);

	SDL_Rect greenRect = energyBarRect;

	greenRect.w = (Uint16)((Singleton::player->energy * (int)energyBarRect.w) / Singleton::player->maxEnergy);
	greenBar->RenderCopy(&greenRect);
}

void GamePanel::ShowPowerUps() {

	SDL_Rect powerUpRect = powerUpsRect;

	redNumbers->RenderCopy(&powerUpRect, Singleton::player->power); 
	powerUpRect.x += 12;

	greenNumbers->RenderCopy(&powerUpRect, Singleton::player->distance); 
	powerUpRect.x += 12;

	blueNumbers->RenderCopy(&powerUpRect, Singleton::player->doubleJumps);
}
