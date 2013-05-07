#pragma once

#include <SFML/Graphics.hpp>
#include "base_system.h"
#include "sprite.h"

class EnergyBar : public BaseSystem {
	public:

		static const int MaxEnergy;
		EnergyBar();
		~EnergyBar();

		void Init();
		void Terminate();

		void Render();

		void SetEnergy(const int energy);
		sf::IntRect rect;

	protected:
		int energy;
		int maxEnergy;
		
		Sprite* greenBar;
		Sprite* redBar;


};
