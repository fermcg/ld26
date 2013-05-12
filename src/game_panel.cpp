#include "game_panel.h"
#include "singletons.h"
#include "ResourcePath.hpp"

#include <sstream>

using std::ostringstream;

GamePanel::GamePanel() : BaseSystem("GamePanel") {
}

GamePanel::~GamePanel() {
}

void GamePanel::Init() {

	this->BaseSystem::Init();

	greenBar = Singleton::spriteMap->Get("ENERGY+G");
	redBar = Singleton::spriteMap->Get("ENERGY+R");

	whiteNumbers  = Singleton::spriteMap->Get("NUMBERS+W");
	redNumbers = Singleton::spriteMap->Get("NUMBERS+R");
	greenNumbers = Singleton::spriteMap->Get("NUMBERS+G");
	blueNumbers = Singleton::spriteMap->Get("NUMBERS+B");

	energyBarRect.left = Singleton::screen->window->getSize().x / 4 - (greenBar->rect.width * 2 + 48) / 2;
	energyBarRect.top = 10;
	energyBarRect.width = greenBar->rect.width;
	energyBarRect.height = greenBar->rect.height;

	powerUpsRect.left = energyBarRect.left + energyBarRect.width + 8;
	powerUpsRect.top = energyBarRect.top;
	powerUpsRect.width = 8;
	powerUpsRect.height = 8;
	
	scorePosition.x = (float)powerUpsRect.left + 40;
	scorePosition.y = (float)energyBarRect.top;
	
	float width = (float) Singleton::screen->window->getSize().x;
	float height = (float) Singleton::screen->window->getSize().y;
	view.setSize(width / 2.0, height / 2.0);
	view.setCenter(width / 4.0, height / 4.0);
	view.setViewport(sf::FloatRect(0.0,0.0,1.0,1.0));
}

void GamePanel::Terminate() {

	this->BaseSystem::Terminate();
}

void GamePanel::Render() {

	Singleton::screen->window->setView(view);
	ShowEnergyBar();
	ShowPowerUps();
	ShowScore();
	Singleton::screen->window->setView(Singleton::screen->view);
}

void GamePanel::ShowEnergyBar() {

	sf::IntRect redRect = energyBarRect;
	redBar->RenderCopy(&redRect);

	sf::IntRect greenRect = energyBarRect;

	greenRect.width = (int)((Singleton::player->energy * (int)energyBarRect.width) / Singleton::player->maxEnergy);
	greenBar->RenderCopy(&greenRect);
}

void GamePanel::ShowPowerUps() {

	sf::IntRect powerUpRect = powerUpsRect;

	redNumbers->RenderCopy(&powerUpRect, Singleton::player->power); 
	powerUpRect.left += 8;

	greenNumbers->RenderCopy(&powerUpRect, Singleton::player->distance); 
	powerUpRect.left += 8;

	blueNumbers->RenderCopy(&powerUpRect, Singleton::player->doubleJumps);
}

void GamePanel::ShowScore() {
	
	int vScore[10];

	int remaining = Singleton::gameLoop->score;
	int start;
	for (start = 9; remaining > 0; start--) {

		int digit = remaining % 10;
		remaining = remaining / 10;

		vScore[start] = digit;
	}

	start++;
	sf::IntRect scoreRect;

	scoreRect.left = scorePosition.x;
	scoreRect.top = scorePosition.y;
	scoreRect.width = 8;
	scoreRect.height = 8;

	for (int i = start; i < 10; i++) {

		whiteNumbers->RenderCopy(&scoreRect, vScore[i]);
		scoreRect.left += 6;
	}
}
