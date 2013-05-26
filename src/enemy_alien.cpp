#include "enemy_alien.h"

EnemyAlien::EnemyAlien()
: Enemy("EnemyAlien", "Enemy Alien") {
	
	unbreakable = false;
	lethal = false;
	solid = false;
	isAlien = true;
	gravity = false;

	neverLeaveArea = true;

	boundingBox.left = 2;
	boundingBox.top = 1;
	boundingBox.width = 4;
	boundingBox.height = 7;
	
	bAcceleration = 0.007;
	maxSpeed = 3.0;

	damage = 1500;
	
	xMaxSpeed = maxSpeed;
	yMaxSpeed = maxSpeed;
}

EnemyAlien::~EnemyAlien() {
}

void EnemyAlien::HandleLogic() {
	
	this->AccelerableObject::HandleLogic();
}

void EnemyAlien::Init() throw() {
	
	this->AccelerableObject::Init();

	// Patrol center is the starting position.
//	patrolX = x;
//	patrolY = y;

	// Patrol range
	minX = x - (double)w * 20;
	maxX = x + (double)w * 20;

	// Position it as close to the floor as wanted at the map
	minY = y - (double)h * 10;
	maxY = y;
}

void EnemyAlien::Terminate() {
	
	this->AccelerableObject::Terminate();
}

void EnemyAlien::TakeThisHit(const int damage) {

	this->AccelerableObject::TakeThisHit(damage);

	this->xSpeed = this->xSpeed / ((800.0 + damage) / 500.0);
	this->ySpeed = this->ySpeed / ((800.0 + damage) / 500.0);
}
SpriteFace* EnemyAlien::CreateSpriteFace() {
	
	SpriteFace* face = new SpriteFace("Enemy Alien Face");
	
	face->RegisterFace(SpriteFace::front, "ALIEN");
	face->RegisterFace(SpriteFace::dying, "ALIEN+DEATH");
	face->ChangeFace(SpriteFace::front);

	face->GetSequence()->counterTarget = 10;
	return face;
}

