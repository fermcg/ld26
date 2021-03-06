#include "enemy.h"

Enemy::Enemy(const char* name, const char* objectId)
: AccelerableObject(name, objectId) {

	isHurting = true;
	isEnemy = true;
}

Enemy::~Enemy() {
}

void Enemy::HandleLogic() {

	this->AccelerableObject::HandleLogic();
}

void Enemy::Init() throw() {

	this->AccelerableObject::Init();
}

void Enemy::Terminate() {

	this->AccelerableObject::Terminate();
}
