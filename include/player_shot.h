#pragma once

#include "projectile.h"
#include "player.h"

class PlayerShot : public Projectile {
	public:
		PlayerShot(Player& father, Projectile::Direction direction, const int distance);
		~PlayerShot();

		void HandleLogic();
		void OnCollision(GameObject& other);
	protected:
		SpriteFace* CreateSpriteFace();
		int distance;
};
