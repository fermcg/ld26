#pragma once

#include <map>

#include "base_system.h"
#include "game_object.h"

using namespace std;

class AccelerableObject;
class AllObjects : public BaseSystem {
	public:
		AllObjects();
		virtual ~AllObjects();

		void Init();
		void Terminate();

		void RegisterObject(GameObject* gameObject);

		void HandleLogic();
		virtual void Render();

		bool LoopCheckForCollision(GameObject& gameObject);

		virtual GameObject* CreateObject(const string& objectClass);
		void HoldMeBack(AccelerableObject& other);

		friend class GameObject;

	protected:
		bool UnregisterObject(unsigned long gameObjectId);

	private:
		typedef map< unsigned long, GameObject* > ObjectMap;
		ObjectMap objectMap;
		unsigned long currentId;
};
