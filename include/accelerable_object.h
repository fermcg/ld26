#pragma once

#include "game_object.h"

class AccelerableObject : public GameObject {

	public:	
		AccelerableObject(const char* name, const char* objectId);
		~AccelerableObject();

		virtual void HandleLogic();

		void GetNewCollisionBox(int& x0, int& y0, int& xf, int& yf) const;
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
		double gAcceleration;

		double minX;
		double maxX;
		double minY;
		double maxY;

		double newX;
		double newY;

		bool grounded;
		bool gravity;

	private:
		bool neverLeaveScreen;
};
