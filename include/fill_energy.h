#pragma once

#include <string>
#include "power_up.h"

using std::string;

class FillEnergy : public PowerUp {

	public:

		FillEnergy(const char* fillEnergySprite, const int energyAmmount);
		~FillEnergy();

		void Init() throw();
		void Terminate();

		void HandleLogic();
		void OnCollision(GameObject& other);

		friend class Player;
	protected:

		SpriteFace* CreateSpriteFace();
		int energyAmmount;
		string fillEnergySprite;
};
