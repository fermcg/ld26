#pragma once

#include <map>

#include "base_system.h"
#include "game_object.h"

using namespace std;

class AccelerableObject;
class AllObjects : public BaseSystem {
	public:
		typedef map< unsigned long, GameObject* > ObjectMap;

		AllObjects();
		virtual ~AllObjects();

		void Init();
		void Terminate();

		virtual void RegisterObject(GameObject* gameObject);
		virtual bool UnregisterObject(unsigned long gameObjectId);

		virtual void HandleLogic();
		virtual void Render();

		virtual bool LoopCheckForCollision(GameObject& gameObject);

		virtual GameObject* CreateObject(const string& objectClass,
										 const string& objectSequence,
										  const double x, const double y,
										  const bool respawn);

		virtual void HoldMeBack(AccelerableObject& other);
		virtual bool AmIGrounded(const AccelerableObject& other);

		virtual void TerminateObject(ObjectMap::iterator itDead);

		friend class GameObject;

		GameObject* groundObject;
	protected:
		ObjectMap objectMap;

	private:
		unsigned long currentId;
};
