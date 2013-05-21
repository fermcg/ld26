#include "game_panel.h"
#include "singletons.h"
#include "ResourcePath.hpp"

#include <sstream>
#include <iostream>

using namespace std;

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

	life = Singleton::spriteMap->Get("LIFE");
	charLowerX = Singleton::spriteMap->Get("CHAR+L+X");

	energyBarRect.left = Singleton::screen->window->getSize().x / 4 - (greenBar->rect.width * 2 + 48) / 2;
	energyBarRect.top = 10;
	energyBarRect.width = greenBar->rect.width;
	energyBarRect.height = greenBar->rect.height;

	livesPosition.x = energyBarRect.left - 4 - charLowerX->rect.width - 6 * 2 - life->rect.width;
	livesPosition.y = energyBarRect.top;


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
	ShowLives();
	ShowEnergyBar();
	ShowPowerUps();
	ShowScore();
	Singleton::screen->window->setView(Singleton::screen->view);
}

void GamePanel::ShowLives() {

	sf::IntRect rect;
	
	rect.left = livesPosition.x;
	rect.top = livesPosition.y;

	rect.width = life->sRect.width;
	rect.height = life->sRect.height;

	life->RenderCopy(&rect);

	rect.left += 8;
	charLowerX->RenderCopy(&rect);

	sf::Vector2f numPosition = livesPosition;
	numPosition.x = rect.left + 8;

	if (Singleton::player->lifes >= 0) {

		this->ShowNumber(numPosition, whiteNumbers, Singleton::player->lifes);
	}
}

void GamePanel::ShowEnergyBar() {

	sf::IntRect redRect = energyBarRect;
	redBar->RenderCopy(&redRect);

	sf::IntRect greenRect = energyBarRect;


	double factor = (double)Singleton::player->energy / (double)Singleton::player->maxEnergy;

	if (factor > 1.0) {

		factor = 1.0;
	}
	if (factor < 0.0) {

		factor = 0.0;
	}
	greenRect.width = (int)((double)energyBarRect.width * factor);
	greenBar->sRect.width = greenRect.width;
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
	
	ShowNumber(scorePosition, whiteNumbers, Singleton::gameLoop->score);
}

void GamePanel::ShowNumber(const sf::Vector2f& position, Sprite* numberSprite, const unsigned int number) {

	unsigned int vNumber[10];

	unsigned int remaining = number;
	unsigned int start;
	for (start = 9; remaining != 0; start--) {

		int digit = remaining % 10;
		remaining = remaining / 10;

		vNumber[start] = digit;
	}

	if (start == 9) {

		vNumber[start] = 0;
		start--;
	}

	start++;
	sf::IntRect rect;

	rect.left = position.x;
	rect.top = position.y;
	rect.width = 8;
	rect.height = 8;

	for (int i = start; i < 10; i++) {

		numberSprite->RenderCopy(&rect, vNumber[i]);
		rect.left += 6;
	}
}