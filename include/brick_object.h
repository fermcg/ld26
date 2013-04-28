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
		void HandleLogic();
		void OnCollision();

		bool Merge(GameObject* other);
		bool Merge(BrickObject* other);

	protected:

		int nx;
		int ny;
};
