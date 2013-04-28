#pragma once

#include "lethal_block.h"

class SpikeBlock : public LethalBlock {

	public:
		SpikeBlock();
		~SpikeBlock();

		void Init() throw();
		void Terminate();
		SpriteFace* CreateSpriteFace();
};

