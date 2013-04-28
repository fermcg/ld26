#pragma once

#include "brick_object.h"

class EmptyBlock : public BrickObject {

	public:
		EmptyBlock();
		~EmptyBlock();

		void Init() throw();
		void Terminate();
		void Render();
		SpriteFace* CreateSpriteFace();
};

