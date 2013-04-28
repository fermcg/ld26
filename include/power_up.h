#pragma once

#include "game_object.h"

class PowerUp : public GameObject {

	public:

		PowerUp(const char* name, const char* objectId);
		~PowerUp();

		virtual void Init() throw();
		virtual void Terminate();

		virtual void HandleLogic();
		virtual void OnCollision(GameObject& other);
};
