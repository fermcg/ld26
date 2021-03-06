#include <iostream>
#include "player_shot.h"

using namespace std;

PlayerShot::PlayerShot(Player& father, Projectile::Direction direction, const int distance, const int power) : Projectile("PlayerShot", "shot") {

	this->direction = direction;
	this->distance = distance * 8;

	yAcceleration = 0.0;
	xAcceleration = 0.0;

	double bAcceleration = 1.0;

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
	xMaxSpeed = 3.5;
	yMinSpeed = 0.0;
	yMaxSpeed = 3.5;

	xBreaking = 0.002;
	yBreaking = 0.002;

	boundingBox.left = 3;
	boundingBox.top = 3;
	boundingBox.width = 2;
	boundingBox.height = 2;

	this->w = 8;
	this->h = 8;
	this->x = father.x;
	this->y = father.y + father.h/2 - 1;

	energy = 1;
	damage = 300 + 100*power;
}

PlayerShot::~PlayerShot() {

}

SpriteFace* PlayerShot::CreateSpriteFace() {

	SpriteFace* face = new SpriteFace("Shot Face");

	face->RegisterFace(SpriteFace::front, "PLAYER+SHOT");

	return face;
}

void PlayerShot::HandleLogic() {

	double oldX = x;
	double oldY = y;

	this->Projectile::HandleLogic();

	double diff = x - oldX;
	if(diff == 0.0) {

		diff = y - oldY;
	}

	if(diff < 0.0) {

		diff = -diff;
	}

	distance -= (int)diff;

	if(distance <= 0) {

		dead = true;
	}
}

void PlayerShot::OnCollision(GameObject& other) {

	if(other.unbreakable) {

		dead = true;
	}

	this->Projectile::OnCollision(other);


}
