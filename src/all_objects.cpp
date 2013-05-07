#include <iostream>

#include "all_objects.h"
#include "macros.h"
#include "exceptions.h"

#include "empty_block.h"
#include "door_object.h"
#include "teal_brick.h"
#include "teal_cracked_brick.h"
#include "lethal_empty_block.h"
#include "spike_block.h"
#include "number_power.h"
#include "accelerable_object.h"

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

void AllObjects::HoldMeBack(AccelerableObject& other) {

	if(other.isProjectile) {

		return;
	}
	AllObjects::ObjectMap::iterator it;

	for(it = objectMap.begin(); it != objectMap.end(); it++) {

		it->second->HoldMeBack(other);
	}
}

bool AllObjects::AmIGrounded(const AccelerableObject& other) {

	AllObjects::ObjectMap::iterator it;

	for(it = objectMap.begin(); it != objectMap.end(); it++) {

		if(it->second->AmIGrounded(other)) {
			
			return true;
		}
	}

	return false;
}

bool AllObjects::LoopCheckForCollision(GameObject& gameObject) {
	AllObjects::ObjectMap::iterator it;
	bool result = false;

	static bool only_one_time = true;
	for(it = objectMap.begin(); it != objectMap.end(); it++) {

		if(it->second->CheckCollision(gameObject)) {

			it->second->TakeThisHit(gameObject.damage);
			gameObject.TakeThisHit(it->second->damage);

			it->second->OnCollision(gameObject);
			gameObject.OnCollision(*it->second);
			result = true;

		}
		if(only_one_time) {

			cout << "name: " << it->second->name << endl;
		}
	}
	only_one_time = false;

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

	GameObject* object = NULL;
	if(objectClass == "EMPTY") {

		object = new EmptyBlock();
	} else if(objectClass.substr(0, 5) == "DOOR>") {

		object = new DoorObject(objectClass.substr(5).c_str());
	} else if(objectClass == "BRICK+TEAL") {

		object = new TealBrick();
	} else if(objectClass == "CRACK+TEAL") {

		object = new TealCrackedBrick();
	} else if(objectClass == "DEATH") {

		object = new LethalEmptyBlock();
	} else if(objectClass == "SPIKES") {

		object = new SpikeBlock();
//	} else if(objectClass == "BOUNCING+ENEMY") {
//
//		object = new BouncingEnemy();
	} else if(objectClass.substr(2, 7) == "NUMBER>") {

		if(objectClass.size() != 10) {

			return NULL;
		}

		int number = objectClass[9] - '0';

		if(number < 0 || number > 9) {

			return NULL;
		}

		switch(objectClass[0]) {
			case 'R':
				object = new NumberPower(NumberPower::red, number);
				break;
			case 'G':
				object = new NumberPower(NumberPower::green, number);
				break;
			case 'B':
				object = new NumberPower(NumberPower::blue, number);
				break;
			default:
				return NULL;
		}
	}

	if(object != NULL) {

		object->Init();
		RegisterObject(object);
	}

	return object;
}
