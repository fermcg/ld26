#pragma once

#include "power_up.h"

class NumberPower : public PowerUp {

	public:

		enum Color {
			red = 0,
			green,
			blue
		};

		NumberPower(const Color color, const int number);
		~NumberPower();

		void Init() throw();
		void Terminate();

		void HandleLogic();
		void OnCollision(GameObject& other);

		friend class Player;
	protected:

		SpriteFace* CreateSpriteFace();
		Color color;
		int number;
};
