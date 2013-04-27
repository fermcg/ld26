#pragma once

#include <map>

#include "base_system.h"
#include "game_object.h"

using namespace std;

class AllObjects : public BaseSystem {
public:
	AllObjects();
	~AllObjects();

	void Init();
	void Terminate();
	
	void RegisterObject(GameObject* gameObject);
	
	void HandleLogic();
	void Render();

	bool LoopCheckForCollision(GameObject& gameObject);
	friend class GameObject;
	
protected:
	bool UnregisterObject(unsigned long gameObjectId);
	
private:
	typedef map< unsigned long, GameObject* > ObjectMap;
	ObjectMap objectMap;
	unsigned long currentId;
};
