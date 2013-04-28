#pragma once

#include "game_object.h"

class AccelerableObject : public GameObject {

	public:	
		AccelerableObject(const char* name, const char* objectId);
		~AccelerableObject();

		virtual void HandleLogic();

		void GetNewCollisionBox(Sint16& x0, Sint16& y0, Sint16& xf, Sint16& yf) const;
		friend class GameObject;
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

		double newX;
		double newY;

	private:
		bool neverLeaveScreen;
};
