#pragma once

#include "accelerable_object.h"

class Enemy : public AccelerableObject {
	
public:
	Enemy(const char* name, const char* objectId);
	~Enemy();
	
	void HandleLogic();
	
	void Init() throw();
	void Terminate();
};
