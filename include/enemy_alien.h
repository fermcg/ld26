#pragma once

#include "enemy.h"

class EnemyAlien : public Enemy {
	
public:
	EnemyAlien();
	~EnemyAlien();
	
	void HandleLogic();
	
	void Init() throw();
	void Terminate();

	void TakeThisHit(const int damage);
	
protected:
	SpriteFace* CreateSpriteFace();
	
	double bAcceleration;
	double maxSpeed;
	
//	double patrolX;
//	double patrolY;
};
