#include "enemy.h"

unsigned long Enemy::objectCount = 0;

Enemy::Enemy() : AccelerableObject("Enemy", "Enemy") {

	bAcceleration = 0.0002;
	// Accelerable vars

	xMinSpeed = 0.0;
	xMaxSpeed = 0.25;
	yMinSpeed = 0.0;
	yMaxSpeed = 0.25;

	xBreaking = 0.0002;
	yBreaking = 0.0002;

	xAcceleration = bAcceleration;
	yAcceleration = bAcceleration / 2.0;

	boundingBox.left = 0;
	boundingBox.top = 9;
	boundingBox.width = 32;
	boundingBox.height = 16;

	Enemy::objectCount++;

	energy = 100;
	damage = 1000;
}

Enemy::~Enemy() {

	Enemy::objectCount--;
}

void Enemy::HandleLogic() {

	if(x < minX + bAcceleration) {

		xAcceleration = bAcceleration;
	} else if(x > maxX - bAcceleration) {

		xAcceleration = -bAcceleration;
	}

	if(y < minY + bAcceleration) {

		yAcceleration = bAcceleration / 2.0;
	} else if(y > maxY - bAcceleration) {

		yAcceleration = -bAcceleration / 2.0;
	}

	this->AccelerableObject::HandleLogic();
}

void Enemy::Init() throw() {

	this->AccelerableObject::Init();

	SetNeverLeaveScreen(true);
	maxY = maxY / 2.0;
	minY = maxY / 15.0;

	x = (maxX - minX) / 2.0;
	y = maxY;
}

void Enemy::Terminate() {

	this->AccelerableObject::Terminate();
}
