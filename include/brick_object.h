#pragma once

#include "game_object.h"

class BrickObject : public GameObject {

	public:

		static const int Width;
		static const int Height;	
		BrickObject(const char* name, const char* objectId);
		~BrickObject();

		virtual void Init() throw();
		virtual void Terminate();

		virtual void Render();
		virtual void HandleLogic();
		virtual void OnCollision(GameObject& object);

		bool Merge(GameObject* other);
		bool Merge(BrickObject* other);

	protected:

		int xSize;
		int ySize;
};
