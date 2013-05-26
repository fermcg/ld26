#pragma once

#include "enemy.h"

class EnemyDog : public Enemy {
	
public:
	EnemyDog();
	~EnemyDog();
	
	void HandleLogic();
	
	void Init() throw();
	void Terminate();

	void TakeThisHit(const int damage);
	
protected:
	SpriteFace* CreateSpriteFace();
	
	double bAcceleration;
	double maxSpeed;
};
