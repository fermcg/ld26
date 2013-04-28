#include <iostream>

#include "all_objects.h"
#include "macros.h"
#include "exceptions.h"

#include "empty_block.h"
#include "door_object.h"

using namespace std;

AllObjects::AllObjects() : BaseSystem("AllObjects") {

	currentId = 0;
}

AllObjects::~AllObjects() {

}

void AllObjects::Init() {

	this->BaseSystem::Init();
}
void AllObjects::Terminate() {

	AllObjects::ObjectMap::iterator it;
	for(it = objectMap.begin(); it != objectMap.end(); it++) {

		GameObject* gameObject = it->second;
		gameObject->gameObjectId = 0; // avoid unregister.
		gameObject->Terminate();
		delete gameObject;
	}
	objectMap.clear();
	this->BaseSystem::Terminate();
}

void AllObjects::RegisterObject(GameObject* gameObject) {

	if(currentId == (unsigned long)0xffffffff) {

		cerr << "Object Id Overflow" << endl;
		THROWINFO(Exception::Overflow, "AllObjects");
	}

	currentId++;
	gameObject->gameObjectId = currentId;
	objectMap[currentId] = gameObject;
}

void AllObjects::HandleLogic() {
	AllObjects::ObjectMap::iterator it;

	it = objectMap.begin();
	while(it!=objectMap.end()) {

		if(it->second->dead) {

			AllObjects::ObjectMap::iterator itDead = it;
			it++;

			itDead->second->gameObjectId = 0;
			itDead->second->Terminate();
			delete itDead->second;
			itDead->second = NULL;
			objectMap.erase(itDead);
		} else {

			it->second->HandleLogic();
			it++;
		}
	}
}

void AllObjects::Render() {
	AllObjects::ObjectMap::iterator it;

	for(it = objectMap.begin(); it != objectMap.end(); it++) {

		it->second->Render();
	}	
}

bool AllObjects::LoopCheckForCollision(GameObject& gameObject) {
	AllObjects::ObjectMap::iterator it;
	bool result = false;

	for(it = objectMap.begin(); it != objectMap.end(); it++) {

		if(it->second->CheckCollision(gameObject)) {

			it->second->TakeThisHit(gameObject.damage);
			gameObject.TakeThisHit(it->second->damage);

			it->second->OnCollision();
			gameObject.OnCollision();
			result = true;
		}
	}

	return result;
}

bool AllObjects::UnregisterObject(unsigned long gameObjectId) {

	AllObjects::ObjectMap::iterator it;

	it = objectMap.find(gameObjectId);
	if(it == objectMap.end()) {

		return false;
	}

	it->second->gameObjectId = 0;
	objectMap.erase(it);

	return true;
}

GameObject* AllObjects::CreateObject(const string& objectClass) {

	if(objectClass == "EMPTY") {

		return new EmptyBlock();
	} else if(objectClass.substr(0, 5) == "DOOR>") {

		return new DoorObject(objectClass.substr(5).c_str());
	} /*
		 } else if(objectClass == "BRICK+TEAL") {

		 return new TealBrick();
		 } else if(objectClass == "CRACK+TEAL") {

		 return new TealCrackedBrick();
		 } else if(objectClass == "DEATH") {

		 return new EmptyLethalBlock();
		 } else if(objectClass == "SPIKES") {

		 return new SpikesBlock;
		 } else if(objectClass.substr(0, 9) == "B.NUMBER>") {

		 return new NumberPower(NumberPower::blue, objectClass.substr(9));
		 } else if(objectClass.substr(0, 9) == "R.NUMBER>") {

		 return new NumberPower(NumberPower::red, objectClass.substr(9));
		 } else if(objectClass.substr(0, 9) == "G.NUMBER>") {

		 return new NumberPower(NumberPower::green, objectClass.substr(9));
		 }*/

return NULL;
}

