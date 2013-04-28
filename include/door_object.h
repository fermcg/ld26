#pragma once

#include "game_object.h"

class DoorObject : public GameObject {

	public:

		DoorObject(const char* name);
		~DoorObject();

		virtual void Init() throw();
		virtual void Terminate();

		SpriteFace* CreateSpriteFace();

	protected:

		string stageId;
};
