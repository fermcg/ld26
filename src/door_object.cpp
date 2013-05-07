#include <iostream>

#include "door_object.h"
#include "stage.h"
#include "singletons.h"

using namespace std;

DoorObject::DoorObject(const char* stageId) : GameObject("Door", "Door") {

	this->stageId = stageId;
	isDoor = true;
	boundingBox.left = 0;
	boundingBox.top = 0;
	boundingBox.width = 8;
	boundingBox.height = 16;

	unbreakable = true;
	damage = 0;
	energy = 10000;

}

DoorObject::~DoorObject() {

}

void DoorObject::Init() throw() {

	this->GameObject::Init();
}

void DoorObject::Terminate() {

	this->GameObject::Terminate();
}

SpriteFace* DoorObject::CreateSpriteFace() {

	SpriteFace* face = new SpriteFace("Door Face");

	face->RegisterFace(SpriteFace::closed, "DOOR+CLOSED");
	face->RegisterFace(SpriteFace::opened, "DOOR+OPENED");

	face->ChangeFace(SpriteFace::closed);

	return face;
}
void DoorObject::OnCollision(GameObject& other) {

	if(other.isPlayer) {

		spriteFace->ChangeFace(SpriteFace::opened);
	}

	this->GameObject::OnCollision(other);
}
void DoorObject::HandleLogic() {

	spriteFace->ChangeFace(SpriteFace::closed);
	this->GameObject::HandleLogic();
}

bool DoorObject::Enter(Player* player) {
	
	Stage* nextStage = Singleton::stageMap->Get(stageId.c_str());
	if(nextStage != NULL) {

		Singleton::gameLoop->currentStage = nextStage;
		nextStage->PositionPlayer();

		return true;
	}

	return false;
}
