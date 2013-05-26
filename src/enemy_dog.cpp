#include "enemy_dog.h"

EnemyDog::EnemyDog()
: Enemy("EnemyDog", "Enemy Dog") {
	
	unbreakable = false;
	lethal = false;
	solid = false;
	isDog = true;
	gravity = true;

	boundingBox.left = 2;
	boundingBox.top = 2;
	boundingBox.width = 4;
	boundingBox.height = 6;
	
	bAcceleration = 0.007;
	maxSpeed = 3.0;

	damage = 1500;
	
	xMaxSpeed = maxSpeed;
	yMaxSpeed = maxSpeed;
}

EnemyDog::~EnemyDog() {
}

void EnemyDog::HandleLogic() {
	
	this->AccelerableObject::HandleLogic();
}

void EnemyDog::Init() throw() {
	
	this->AccelerableObject::Init();
}

void EnemyDog::Terminate() {
	
	this->AccelerableObject::Terminate();
}

void EnemyDog::TakeThisHit(const int damage) {

	this->AccelerableObject::TakeThisHit(damage);

	this->xSpeed = this->xSpeed / ((800.0 + damage) / 500.0);
	this->ySpeed = this->ySpeed / ((800.0 + damage) / 500.0);
}
SpriteFace* EnemyDog::CreateSpriteFace() {
	
	return CreateWalkingCharFace("DOG");
}

