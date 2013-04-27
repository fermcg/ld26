#pragma once

#include "accelerable_object.h"

class Projectile : public AccelerableObject {

public:	
	Projectile(const char* name, const char* objectId);
	~Projectile();
	
	virtual void HandleLogic();
	
protected:
};
