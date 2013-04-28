#pragma once

#include "lethal_block.h"

class LethalEmptyBlock : public LethalBlock {

	public:
		LethalEmptyBlock();
		~LethalEmptyBlock();

		void Init() throw();
		void Terminate();
		void Render();
		SpriteFace* CreateSpriteFace();
};

