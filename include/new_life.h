#pragma once

#include "power_up.h"

class NewLife : public PowerUp {

	public:

		NewLife();
		~NewLife();

		void Init() throw();
		void Terminate();

		void HandleLogic();
		void OnCollision(GameObject& other);

		friend class Player;
	protected:

		SpriteFace* CreateSpriteFace();
};
