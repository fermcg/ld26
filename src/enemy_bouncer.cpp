#include "enemy_bouncer.h"

EnemyBouncer::EnemyBouncer(const double xSpeed, const double ySpeed)
: Enemy("EnemyBouncer", "Enemy Bouncer") {
	
	unbreakable = true;
	lethal = false;
	solid = false;
	isBouncer = true;
	gravity = false;

	boundingBox.left = 1;
	boundingBox.top = 2;
	boundingBox.width = 5;
	boundingBox.height = 5;
	
	bAcceleration = 0.007;
	maxSpeed = 3.0;

	damage = 1500;
	
	xMaxSpeed = maxSpeed;
	yMaxSpeed = maxSpeed;
	
	this->xSpeed = xSpeed;
	this->ySpeed = ySpeed;
	
	if (this->xSpeed > 0.0) {
		
		this->xAcceleration = bAcceleration;
	} else if (this->xSpeed < 0.0) {
		
		this->xAcceleration = -bAcceleration;
	}
	
	if (this->ySpeed > 0.0) {
		
		this->yAcceleration = bAcceleration;
	} else if (this->ySpeed < 0.0) {
		
		this->yAcceleration = -bAcceleration;
	}
}

EnemyBouncer::~EnemyBouncer() {
}

void EnemyBouncer::HandleLogic() {
	
	this->AccelerableObject::HandleLogic();
}

void EnemyBouncer::Init() throw() {
	
	this->AccelerableObject::Init();
}

void EnemyBouncer::Terminate() {
	
	this->AccelerableObject::Terminate();
}

void EnemyBouncer::TakeThisHit(const int damage) {

	this->AccelerableObject::TakeThisHit(damage);

	this->xSpeed = this->xSpeed / ((800.0 + damage) / 500.0);
	this->ySpeed = this->ySpeed / ((800.0 + damage) / 500.0);
}
SpriteFace* EnemyBouncer::CreateSpriteFace() {
	
	SpriteFace* face = new SpriteFace("Enemy Bouncer Face");
	
	face->RegisterFace(SpriteFace::front, "BOUNCER");
	face->ChangeFace(SpriteFace::front);

	face->GetSequence()->counterTarget = 10;
	return face;
}

