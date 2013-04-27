#include "player_shot.h"

PlayerShot::PlayerShot(Player& father) : Projectile("PlayerShot", "shot", "PLAYER+SHOT") {
	
	yAcceleration = -0.01;
	xAcceleration = 0.0;
	
	// Accelerable vars
	
	xMinSpeed = 0.0;
	xMaxSpeed = 0.0;
	yMinSpeed = 0.0;
	yMaxSpeed = 2.0;
	
	xBreaking = 0.0002;
	yBreaking = 0.0002;
			
	boundingBox.x = 14;
	boundingBox.y = 1;
	boundingBox.w = 6;
	boundingBox.h = 32;
	
	this->w = father.w;
	this->h = father.h;
	this->x = father.x;
	this->y = father.y;
	
	enemy = false;
	
	energy = 1;
	damage = 300;
}

PlayerShot::~PlayerShot() {
	
}

void PlayerShot::HandleLogic() {
	
	this->Projectile::HandleLogic();
}
