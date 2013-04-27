#pragma once

#include "game_object.h"

class AccelerableObject : public GameObject {

public:	
	AccelerableObject(const char* name, const char* objectId, const char* spriteId);
	~AccelerableObject();
	
	virtual void HandleLogic();
	
protected:
	void SetNeverLeaveScreen(const bool neverLeaveScreen);
	
	double xMinSpeed;
	double xMaxSpeed;
	double yMinSpeed;
	double yMaxSpeed;
	
	double xBreaking;
	double yBreaking;
	
	double xSpeed;
	double ySpeed;
	
	double xAcceleration;
	double yAcceleration;
	
	double minX;
	double maxX;
	double minY;
	double maxY;
	
private:
	bool neverLeaveScreen;
};
