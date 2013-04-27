#include <iostream>

#include "accelerable_object.h"
#include "singletons.h"

using namespace std;

AccelerableObject::AccelerableObject(const char* name, const char* objectId, const char* spriteId) : GameObject(name, objectId, spriteId) {
	
	xMinSpeed = 0.0;
	xMaxSpeed = 0.0;
	yMinSpeed = 0.0;
	yMaxSpeed = 0.0;
	
	xBreaking = 0.0;
	yBreaking = 0.0;
	
	xSpeed = 0.0;
	ySpeed = 0.0;
	
	xAcceleration = 0.0;
	yAcceleration = 0.0;
	
	neverLeaveScreen = false;
	
	minX = 0.0;
	minY = 0.0;
	maxX = 0.0;
	maxY = 0.0;
}

AccelerableObject::~AccelerableObject() {
	
}

void AccelerableObject::HandleLogic() {
	
	if(xAcceleration > 0.0) {
		
		if(xSpeed < xMaxSpeed) {
			
			xSpeed += xAcceleration;
			if(xSpeed > xMaxSpeed) {
				xSpeed = xMaxSpeed;
			} else if(xSpeed < xMinSpeed) {
				xSpeed = xMinSpeed;
			}
		}
	} else if(xAcceleration < 0.0) {
		
		if(xSpeed > -xMaxSpeed) {
			
			xSpeed += xAcceleration;
			if(xSpeed < -xMaxSpeed) {
				xSpeed = -xMaxSpeed;
			} else if(xSpeed > -xMinSpeed) {
				xSpeed = -xMinSpeed;
			}
		}
	} else if(xBreaking > 0.0) {
		
		if(xSpeed > xMinSpeed) {
			
			xSpeed -= xBreaking;
			if(xSpeed < xMinSpeed) {
				
				xSpeed = xMinSpeed;
			}
		} else if(xSpeed < -xMinSpeed) {
			
			xSpeed += xBreaking;
			if(xSpeed > -xMinSpeed) {
				
				xSpeed = -xMinSpeed;
			}
		}
	}

	if(yAcceleration > 0.0) {
		
		if(ySpeed < yMaxSpeed) {
			
			ySpeed += yAcceleration;
			if(ySpeed > yMaxSpeed) {
				ySpeed = yMaxSpeed;
			}
		} else if(ySpeed < yMinSpeed) {
			ySpeed = yMinSpeed;
		}
	} else if(yAcceleration < 0.0) {
		
		if(ySpeed > -yMaxSpeed) {
			
			ySpeed += yAcceleration;
			if(ySpeed < -yMaxSpeed) {
				ySpeed = -yMaxSpeed;
			}
		} else if(ySpeed > -yMinSpeed) {
			ySpeed = -yMinSpeed;
		}
	} else if(yBreaking > 0.0) {
		
		if(ySpeed > yMinSpeed) {
			
			ySpeed -= yBreaking;
			if(ySpeed < yMinSpeed) {
				
				ySpeed = yMinSpeed;
			}
		} else if(ySpeed < -yMinSpeed) {
			
			ySpeed += yBreaking;
			if(ySpeed > -yMinSpeed) {
				
				ySpeed = -yMinSpeed;
			}
		}
	}
	
	x += xSpeed;
	y += ySpeed;
	
	if(neverLeaveScreen) {
		
		if(x < minX) {
			
			x = minX;
		} else if(x > maxX) {
			
			x = maxX;
		}
		if(y < minY) {
			
			y = minY;
		} else if(y > maxY) {
			
			y = maxY;
		}
	}
	
	this->GameObject::HandleLogic();
}

void AccelerableObject::SetNeverLeaveScreen(const bool neverLeaveScreen) {

	this->neverLeaveScreen = neverLeaveScreen;
	if(neverLeaveScreen) {
		
		int width = 0;
		int height = 0;
		SDL_GetWindowSize(Singleton::screen->window, &width, &height);
		
		minX = 0.0;
		minY = 0.0;
		maxX = (double)width - (double)this->w;
		maxY = (double)height - (double)this->h;
	}
}
