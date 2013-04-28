#include "player_shot.h"

PlayerShot::PlayerShot(Player& father, Projectile::Direction direction) : Projectile("PlayerShot", "shot") {

	this->direction = direction;

	yAcceleration = 0.0;
	xAcceleration = 0.0;

	double bAcceleration = 0.1;

	switch(direction) {

		case Projectile::up:
			yAcceleration = -bAcceleration;
			break;
		case Projectile::down:
			yAcceleration = bAcceleration;
			break;
		case Projectile::left:
			xAcceleration = -bAcceleration;
			break;
		case Projectile::right:
			xAcceleration = bAcceleration;
			break;
	}

	// Accelerable vars

	xMinSpeed = 0.0;
	xMaxSpeed = 2.0;
	yMinSpeed = 0.0;
	yMaxSpeed = 2.0;

	xBreaking = 0.0002;
	yBreaking = 0.0002;

	boundingBox.x = 3;
	boundingBox.y = 3;
	boundingBox.w = 2;
	boundingBox.h = 2;

	this->w = 8;
	this->h = 8;
	this->x = father.x + father.w/2 - 1;
	this->y = father.y + father.h/2 - 1;

	energy = 1;
	damage = 300;
}

PlayerShot::~PlayerShot() {

}

SpriteFace* PlayerShot::CreateSpriteFace() {

	SpriteFace* face = new SpriteFace("Shot Face");

	face->RegisterFace(SpriteFace::front, "PLAYER+SHOT");

	return face;
}

void PlayerShot::HandleLogic() {

	this->Projectile::HandleLogic();
}

void PlayerShot::OnCollision(GameObject& other) {
	
	if(other.unbreakable) {

		dead = true;
	}


}
