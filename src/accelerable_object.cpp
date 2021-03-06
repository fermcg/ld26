#include <iostream>

#include "accelerable_object.h"
#include "singletons.h"

using namespace std;

AccelerableObject::AccelerableObject(const char* name, const char* objectId) : GameObject(name, objectId) {

	xMinSpeed = 0.0;
	xMaxSpeed = 0.0;
	yMinSpeed = 0.0;
	yMaxSpeed = 0.0;

	xBreaking = 0.0;
	yBreaking = 0.0;

	xBreakingAdjust = 1.0;
	yBreakingAdjust = 1.0;
	xAccelerationAdjust = 1.0;
	yAccelerationAdjust = 1.0;

	xSpeed = 0.0;
	ySpeed = 0.0;

	xAcceleration = 0.0;
	yAcceleration = 0.0;

	gAcceleration = 0.0;
	jAcceleration = 0.0;

	neverLeaveArea = false;

	minX = 0.0;
	minY = 0.0;
	maxX = 0.0;
	maxY = 0.0;

	grounded = true;
	gravity = true;
}

AccelerableObject::~AccelerableObject() {

}

void AccelerableObject::HandleLogic() {

	if(gravity && !grounded) {

		yAcceleration = gAcceleration;
	}

	if(xAcceleration > 0.0) {

		if(xSpeed < xMaxSpeed) {

			if(xSpeed < xMinSpeed) { // actually breaking

				xSpeed += xAcceleration * xAccelerationAdjust;
				if(xSpeed > xMaxSpeed) {
					xSpeed = xMaxSpeed;
				} else if(!grounded && xSpeed < xMinSpeed) {
					xSpeed = xMinSpeed;
				}
			} else {

				xSpeed += xAcceleration * xAccelerationAdjust;
				if(xSpeed > xMaxSpeed) {
					xSpeed = xMaxSpeed;
				} else if(xSpeed < xMinSpeed) {
					xSpeed = xMinSpeed;
				}
			}
		}
		//spriteFace->ChangeFace(SpriteFace::right);

	} else if(xAcceleration < 0.0) {

		if(xSpeed > -xMaxSpeed) {

			if(xSpeed > -xMinSpeed) { // actually breaking

				xSpeed += xAcceleration * xAccelerationAdjust;
				if(xSpeed < -xMaxSpeed) {
					xSpeed = -xMaxSpeed;
				} else if(!grounded && xSpeed > -xMinSpeed) {
					xSpeed = -xMinSpeed;
				}
			} else {

				xSpeed += xAcceleration * xAccelerationAdjust;
				if(xSpeed < -xMaxSpeed) {
					xSpeed = -xMaxSpeed;
				} else if(xSpeed > -xMinSpeed) {
					xSpeed = -xMinSpeed;
				}
			}
		}
		//spriteFace->ChangeFace(SpriteFace::left);

	} else if(xBreaking > 0.0) {

		if(xSpeed > xMinSpeed) {

			xSpeed -= xBreaking * xBreakingAdjust;
			if(xSpeed < xMinSpeed) {

				xSpeed = xMinSpeed;
			}
		} else if(xSpeed < -xMinSpeed) {

			xSpeed += xBreaking * xBreakingAdjust;
			if(xSpeed > -xMinSpeed) {

				xSpeed = -xMinSpeed;
			}
		}
	}

	if(yAcceleration > 0.0) {

		if(ySpeed < yMaxSpeed) {

			if(ySpeed < yMinSpeed) { // actually breaking

				ySpeed += yAcceleration * yBreakingAdjust;
			} else {

				ySpeed += yAcceleration * yAccelerationAdjust;
			}
			if(ySpeed > yMaxSpeed) {
				ySpeed = yMaxSpeed;
			}
		} else if(ySpeed < yMinSpeed) {
			ySpeed = yMinSpeed;
		}
	} else if(yAcceleration < 0.0) {

		if(ySpeed > -yMaxSpeed) {

			if(ySpeed > -yMinSpeed) { // actually breaking

				ySpeed += yAcceleration * yBreakingAdjust;
			} else {

				ySpeed += yAcceleration * yAccelerationAdjust;
			}
			ySpeed += yAcceleration * yAccelerationAdjust;
			if(ySpeed < -yMaxSpeed) {
				ySpeed = -yMaxSpeed;
			}
		} else if(ySpeed > -yMinSpeed) {
			ySpeed = -yMinSpeed;
		}
	} else if(yBreaking > 0.0) {

		if(ySpeed > yMinSpeed ) {

			ySpeed -= yBreaking * yBreakingAdjust;
			if(ySpeed < yMinSpeed) {

				ySpeed = yMinSpeed;
			}
		} else if(ySpeed < -yMinSpeed) {

			ySpeed += yBreaking * yBreakingAdjust;
			if(ySpeed > -yMinSpeed) {

				ySpeed = -yMinSpeed;
			}
		}
	}

	if(xSpeed == 0.0 && xAcceleration == 0.0) {

		//spriteFace->ChangeFace(SpriteFace::front);
	}

	newX = x + xSpeed;
	newY = y + ySpeed;

	Singleton::gameLoop->currentStage->HoldMeBack(*this);

	x = newX;
	y = newY;
	
	if (gravity) {
		grounded = Singleton::gameLoop->currentStage->AmIGrounded(*this);
		cout << "grounded = " << grounded << "   \r";

		if (grounded && Singleton::gameLoop->currentStage->groundObject != NULL) {

			xBreakingAdjust = Singleton::gameLoop->currentStage->groundObject->xAdjust;
			yBreakingAdjust = Singleton::gameLoop->currentStage->groundObject->yAdjust;
			xAccelerationAdjust = Singleton::gameLoop->currentStage->groundObject->xAdjustAcceleration;
			yAccelerationAdjust = Singleton::gameLoop->currentStage->groundObject->yAdjustAcceleration;
		} else {

			xBreakingAdjust = 1.0;
			yBreakingAdjust = 1.0;
			xAccelerationAdjust = 1.0;
			yAccelerationAdjust = 1.0;
		}
	}
	if(neverLeaveArea) {

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

void AccelerableObject::SetNeverLeaveArea(const bool neverLeaveArea) {

	this->neverLeaveArea = neverLeaveArea;
	if(neverLeaveArea) {

		int width = Singleton::screen->window->getSize().x;
		int height = Singleton::screen->window->getSize().y;

		minX = 0.0;
		minY = 0.0;
		maxX = (double)width - (double)this->w;
		maxY = (double)height - (double)this->h;
	}
}

void AccelerableObject::GetNewCollisionBox(int& x0, int& y0, int& xf, int& yf) const {

	x0 = (int)newX + boundingBox.left;
	xf = x0 + boundingBox.width;
	y0 = (int)newY + boundingBox.top;
	yf = y0 + boundingBox.height;
}
