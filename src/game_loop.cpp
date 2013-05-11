#include <SFML/Graphics.hpp>
#include <iostream>
#include "game_loop.h"
#include "singletons.h"
#include "enemy.h"

using namespace std;

GameLoop::GameLoop() : BaseSystem("GameLoop") {

	currentStage = NULL;
	gameOver = false;
	
	score = 0;
}

GameLoop::~GameLoop() {

}

void GameLoop::Init() throw() {

	currentStage = Singleton::stageMap->Get("MENU");
//	currentStage = Singleton::stageMap->Get("STAGE01");

}

void GameLoop::Terminate() {

}

void GameLoop::GameOver() {

	gameOver = true;
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
	currentStage->PositionPlayer();
	//int frameWait = 10;
	//int lastFrame = 0;

	for(loopCount = 0; Singleton::screen->window->isOpen(); loopCount++) {
		LoopStart();
		HandleEvents();
		HandleLogic();

		//while(XDL_GetTicks() - lastFrame < frameWait) {
		//}
		//lastFrame = XDL_GetTicks();
		Render();
		LoopEnd();
	}
}

void GameLoop::LoopStart() {

	/*	if(loopCount % 500 == 0 && Enemy::objectCount < 10) {

		Enemy *enemy = new Enemy();
		enemy->Init();
		Singleton::allEnemies->RegisterObject(enemy);		
		}*/
}

void GameLoop::HandleEvents() {

	// Process events
	sf::Event event;
	while (Singleton::screen->window->pollEvent(event))
	{
		// Close window : exit
		if (event.type == sf::Event::Closed) {
			Singleton::screen->window->close();
		}
		
		
		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
			
			switch (event.key.code) {
					
				case sf::Keyboard::Left:
					Singleton::player->CommandSetOrReset(Player::left, event.type == sf::Event::KeyPressed);
					break;
					
				case sf::Keyboard::Right:
					Singleton::player->CommandSetOrReset(Player::right, event.type == sf::Event::KeyPressed);
					break;
					
				case sf::Keyboard::Up:
					Singleton::player->CommandSetOrReset(Player::up, event.type == sf::Event::KeyPressed);
					break;
					
				case sf::Keyboard::Down:
					Singleton::player->CommandSetOrReset(Player::down, event.type == sf::Event::KeyPressed);
					break;
					
				case sf::Keyboard::Escape:
					if (event.type == sf::Event::KeyPressed) {
						Singleton::screen->window->close();
						continue;
					}
					break;
					
				case sf::Keyboard::X:
					Singleton::player->CommandSetOrReset(Player::fire, event.type == sf::Event::KeyPressed);
					break;
					
				case sf::Keyboard::Z:
					Singleton::player->CommandSetOrReset(Player::jump, event.type == sf::Event::KeyPressed);
					break;
					
				case sf::Keyboard::F:
					if (event.type == sf::Event::KeyPressed) {
						Singleton::screen->ToogleFullScreen();
					}
					break;
				default:
					cout << "Symbol:" << event.key.code << endl;
					break;
			}
		} else if (event.type == sf::Event::JoystickButtonPressed || event.type == sf::Event::JoystickButtonReleased) {

			Singleton::player->CommandSetOrReset(Player::fire, sf::Joystick::isButtonPressed(0, 0));
			Singleton::player->CommandSetOrReset(Player::jump, sf::Joystick::isButtonPressed(0, 1));
		}
	}

	if (sf::Joystick::isConnected(0)) {
		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::PovY);
		float y = -sf::Joystick::getAxisPosition(0, sf::Joystick::PovX);

		if (x < -20.0) {
			Singleton::player->CommandSetOrReset(Player::left, true);
			Singleton::player->CommandSetOrReset(Player::right, false);
		} else if (x > 20.0) {
			Singleton::player->CommandSetOrReset(Player::left, false);
			Singleton::player->CommandSetOrReset(Player::right, true);
		} else if (x > -10.0 && x < 10.0) {
			Singleton::player->CommandSetOrReset(Player::left, false);
			Singleton::player->CommandSetOrReset(Player::right, false);
		}

		if (y < -20.0) {
			Singleton::player->CommandSetOrReset(Player::up, true);
			Singleton::player->CommandSetOrReset(Player::down, false);
		} else if (y > 20.0) {
			Singleton::player->CommandSetOrReset(Player::up, false);
			Singleton::player->CommandSetOrReset(Player::down, true);
		} else if (y > -10.0 && y < 10.0) {
			Singleton::player->CommandSetOrReset(Player::up, false);
			Singleton::player->CommandSetOrReset(Player::down, false);
		}
	}

}

void GameLoop::HandleLogic() {

	Singleton::player->HandleLogic();
	currentStage->HandleLogic();
	Singleton::allFriends->HandleLogic();
//	Singleton::screen->HandleZoom();
//	Singleton::allEnemies->HandleLogic();
	return;
}

void GameLoop::Render() {

	// Clear screen
	//sf::Color(0,0,0,0));

//	Singleton::allEnemies->Render();
	//	Singleton::player->PrintStates();

	currentStage->Render();
	Singleton::allFriends->Render();
	Singleton::player->Render();

	Singleton::screen->window->display();
}

void GameLoop::LoopEnd() {

	if(gameOver) {

		Singleton::stageMap->Terminate();
		delete Singleton::stageMap;
		Singleton::stageMap = new StageMap();
		Singleton::gameLoop->score = 0;
		Singleton::stageMap->Init();
		gameOver = false;

		Stage* nextStage = Singleton::stageMap->Get("MENU");
		if(nextStage != NULL) {

			currentStage = nextStage;
			nextStage->PositionPlayer();
			Singleton::player->Ressurrect();
		} else {

			cerr << "Error" << endl;
		}
	}
}

