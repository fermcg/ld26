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
		void ShowEnergyBar();
		void ShowPowerUps();

		Sprite* greenBar;
		Sprite* redBar;

		Sprite* redNumbers;
		Sprite* greenNumbers;
		Sprite* blueNumbers;

		sf::IntRect energyBarRect;
		sf::IntRect powerUpsRect;
	
};
