#pragma once

#include "accelerable_object.h"

class Projectile : public AccelerableObject {

public:	
	Projectile(const char* name, const char* objectId, const char* spriteId);
	~Projectile();
	
	virtual void HandleLogic();
	
protected:
};
