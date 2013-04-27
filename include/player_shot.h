#pragma once

#include "projectile.h"
#include "player.h"

class PlayerShot : public Projectile {
public:
	PlayerShot(Player& father);
	~PlayerShot();
	
	void HandleLogic();
};