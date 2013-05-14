#pragma once

#include "enemy.h"

class EnemyBouncer : public Enemy {
	
public:
	EnemyBouncer(const double xSpeed, const double ySpeed);
	~EnemyBouncer();
	
	void HandleLogic();
	
	void Init() throw();
	void Terminate();

	void TakeThisHit(const int damage);
	
protected:
	SpriteFace* CreateSpriteFace();
	
	double bAcceleration;
	double maxSpeed;
	
};
