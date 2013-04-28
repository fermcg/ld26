#include "door_object.h"

DoorObject::DoorObject(const char* stageId) : GameObject("Door", "Door") {

	stageId = stageId;
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

	SpriteFace* face = new SpriteFace("Player Face");
	
	face->RegisterFace(SpriteFace::closed, "DOOR+CLOSED");
	face->RegisterFace(SpriteFace::opened, "DOOR+OPENED");

	return face;
}
