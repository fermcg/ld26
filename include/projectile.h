#pragma once

#include "accelerable_object.h"

class Projectile : public AccelerableObject {

	public:

		enum Direction {
			up = 0,
			down,
			left,
			right
		};
		Projectile(const char* name, const char* objectId);
		~Projectile();

		virtual void HandleLogic();

	protected:

		Direction direction;
};
