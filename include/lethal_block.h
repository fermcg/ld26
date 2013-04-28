#pragma once

#include "brick_object.h"

class LethalBlock : public BrickObject {

	public:
		LethalBlock(const char* name, const char* objectId);
		~LethalBlock();

		virtual void Init() throw();
		virtual void Terminate();
};

