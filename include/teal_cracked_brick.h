#pragma once

#include "brick_object.h"

class TealCrackedBrick : public BrickObject {

	public:
		TealCrackedBrick();
		~TealCrackedBrick();

		void Init() throw();
		void Terminate();
		SpriteFace* CreateSpriteFace();
};

