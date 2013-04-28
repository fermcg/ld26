#pragma once

#include "accelerable_object.h"

class Enemy : public AccelerableObject {
	public:
		Enemy();
		~Enemy();

		void HandleLogic();

		void Init() throw();
		void Terminate();

		static unsigned long objectCount;
	private:
		double bAcceleration;

};
