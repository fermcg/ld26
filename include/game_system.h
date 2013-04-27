#pragma once

#include "base_system.h"

class GameSystem : public BaseSystem {
public:
	GameSystem();
	~GameSystem();
	
	void Init() throw();
	void Terminate();
	
	static const int MaxMixChannels;
};