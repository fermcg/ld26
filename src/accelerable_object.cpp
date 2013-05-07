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

	xSpeed = 0.0;
	ySpeed = 0.0;

	xAcceleration = 0.0;
	yAcceleration = 0.0;

	gAcceleration = 0.0;

	neverLeaveScreen = false;

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

			xSpeed += xAcceleration;
			if(xSpeed > xMaxSpeed) {
				xSpeed = xMaxSpeed;
			} else if(xSpeed < xMinSpeed) {
				xSpeed = xMinSpeed;
			}
		}
		//spriteFace->ChangeFace(SpriteFace::right);

	} else if(xAcceleration < 0.0) {

		if(xSpeed > -xMaxSpeed) {

			xSpeed += xAcceleration;
			if(xSpeed < -xMaxSpeed) {
				xSpeed = -xMaxSpeed;
			} else if(xSpeed > -xMinSpeed) {
				xSpeed = -xMinSpeed;
			}
		}
		//spriteFace->ChangeFace(SpriteFace::left);

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

	if(xSpeed == 0.0 && xAcceleration == 0.0) {

		//spriteFace->ChangeFace(SpriteFace::front);
	}

	newX = x + xSpeed;
	newY = y + ySpeed;

	Singleton::gameLoop->currentStage->HoldMeBack(*this);

	grounded = Singleton::gameLoop->currentStage->AmIGrounded(*this);

	cout << "grounded = " << grounded << "   \r";
	x = newX;
	y = newY;
		
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

void AccelerableObject::GetNewCollisionBox(Sint16& x0, Sint16& y0, Sint16& xf, Sint16& yf) const {

	x0 = (Sint16)newX + boundingBox.x;
	xf = x0 + boundingBox.w;
	y0 = (Sint16)newY + boundingBox.y;
	yf = y0 + boundingBox.h;	
}
