#pragma once

#include "brick_object.h"

class TealBrick : public BrickObject {

	public:
		TealBrick();
		~TealBrick();

		void Init() throw();
		void Terminate();
		SpriteFace* CreateSpriteFace();
};

