#include "teal_brick.h"

TealBrick::TealBrick() : BrickObject("TealBrick", "TealBrick") {
}

TealBrick::~TealBrick() {
}

void TealBrick::Init() throw() {

	this->GameObject::Init();
}

void TealBrick::Terminate() {

	this->GameObject::Terminate();
}

SpriteFace* TealBrick::CreateSpriteFace() {

	SpriteFace* face = new SpriteFace("Teal Brick Face");

	face->RegisterFace(SpriteFace::front, "BRICK+TEAL");

	return face;
}

