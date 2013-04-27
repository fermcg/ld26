#pragma once

#include "base_system.h"

class GameLoop : public BaseSystem {
public:
	GameLoop();
	~GameLoop();
	
	void Init() throw();
	void Terminate();
	
	void Loop() throw();
	
private:
	void LoopStart();
	void HandleEvents();
	void HandleLogic();
	void Render();
	void LoopEnd();
	
	bool keepWalking;
	unsigned long loopCount;
};
