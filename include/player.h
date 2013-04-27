#pragma once

#include "accelerable_object.h"

class Player : public AccelerableObject {
public:
	enum Command {
		nothing = 0,
		left,
		right,
		up,
		down,
		fire
	};
	
	Player();
	~Player();
	
	void CommandSetOrReset(const Command& command, const bool set = true);
	
	// Test commands.
	void PrintStates();
	
	void Init() throw();
	void Terminate();
	
	void OnCollision();
	
	friend class PlayerShot;
	
private:
	double bAcceleration;

	bool fireIsOn;
	bool leftIsOn;
	bool rightIsOn;
	bool upIsOn;
	bool downIsOn;
	
	bool accelerationChanged;
	bool fireChanged;	
};
