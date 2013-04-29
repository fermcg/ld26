#pragma once

#include "game_object.h"

class Player;
class DoorObject : public GameObject {

	public:

		DoorObject(const char* name);
		~DoorObject();

		virtual void Init() throw();
		virtual void Terminate();

		virtual void OnCollision(GameObject& other);
		virtual void HandleLogic();
		virtual bool Enter(Player* player);
		SpriteFace* CreateSpriteFace();

	protected:

		string stageId;
};
