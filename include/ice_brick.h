#pragma once

#include "brick_object.h"

class IceBrick : public BrickObject {

	public:
		IceBrick();
		~IceBrick();

		void Init() throw();
		void Terminate();
		SpriteFace* CreateSpriteFace();
};
