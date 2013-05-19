#pragma once

#include <SFML/Graphics.hpp>
#include "base_system.h"
#include "sprite.h"

class GamePanel : public BaseSystem {

	public:
		GamePanel();
		~GamePanel();

		void Init();
		void Terminate();

		void Render();

		sf::View view;

	private:
		void ShowLives();
		void ShowEnergyBar();
		void ShowPowerUps();
		void ShowScore();

		void ShowNumber(const sf::Vector2f& position, Sprite* numberSprite, const unsigned int number);

		Sprite* greenBar;
		Sprite* redBar;

		Sprite* whiteNumbers;
		Sprite* redNumbers;
		Sprite* greenNumbers;
		Sprite* blueNumbers;

		Sprite* life;
		Sprite* charLowerX;

		sf::Vector2f livesPosition;
		sf::IntRect energyBarRect;
		sf::IntRect powerUpsRect;
		sf::Vector2f scorePosition;
	
};
