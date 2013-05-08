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

	redNumbers = Singleton::spriteMap->Get("NUMBERS+R");
	greenNumbers = Singleton::spriteMap->Get("NUMBERS+G");
	blueNumbers = Singleton::spriteMap->Get("NUMBERS+B");

	energyBarRect.left = 640 / 2 - (greenBar->rect.width + 48) / 2;
	energyBarRect.top = 20;
	energyBarRect.width = 80;
	energyBarRect.height = 4;

	powerUpsRect.left = energyBarRect.left + energyBarRect.width + 16;
	powerUpsRect.top = energyBarRect.top;
	powerUpsRect.width = 8;
	powerUpsRect.height = 8;
	
	sf::IntRect scoreRect;
	scorePosition.x = (float)powerUpsRect.left + 48;
	scorePosition.y = (float)energyBarRect.top - 8;
	
	float width = (float) Singleton::screen->window->getSize().x;
	float height = (float) Singleton::screen->window->getSize().y;
	view.setSize(width, height);
	view.setCenter(width / 2.0, height / 2.0);
	view.setViewport(sf::FloatRect(0.0,0.0,1.0,1.0));
	
	font.loadFromFile(resourcePath() + "pixelated.ttf");
	scoreText.setFont(font);
	scoreText.setCharacterSize(10);
}

void GamePanel::Terminate() {

	this->BaseSystem::Terminate();
}

void GamePanel::Render() {

	Singleton::screen->window->setView(view);
	ShowEnergyBar();
	ShowPowerUps();
	ShowScore();
	Singleton::screen->window->setView(*Singleton::screen->view);
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
	powerUpRect.left += 12;

	greenNumbers->RenderCopy(&powerUpRect, Singleton::player->distance); 
	powerUpRect.left += 12;

	blueNumbers->RenderCopy(&powerUpRect, Singleton::player->doubleJumps);
}

void GamePanel::ShowScore() {
	
	ostringstream ss;
	
	ss << Singleton::gameLoop->score;
	
	scoreText.setString(ss.str());
	scoreText.setColor(sf::Color::White);

	scoreText.setPosition(scorePosition);
	Singleton::screen->window->draw(scoreText);
}
