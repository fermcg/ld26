#pragma once

#include <SDL.h>
#include "base_system.h"
#include "sprite.h"

class GamePanel : public BaseSystem {
	public:

		GamePanel();
		~GamePanel();

		void Init();
		void Terminate();

		void Render();


	protected:

	private:
		void ShowEnergyBar();
		void ShowPowerUps();

		Sprite* greenBar;
		Sprite* redBar;

		Sprite* redNumbers;
		Sprite* greenNumbers;
		Sprite* blueNumbers;

		SDL_Rect energyBarRect;
		SDL_Rect powerUpsRect;
};
