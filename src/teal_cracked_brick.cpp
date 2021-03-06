#include "teal_cracked_brick.h"

TealCrackedBrick::TealCrackedBrick() : BrickObject("TealCrackedBrick", "TealCrackedBrick") {

	unbreakable = false;
	stationary = false;
	energy = 300;
	damage = 1;
	scoreValue = 1000;
}

TealCrackedBrick::~TealCrackedBrick() {
}

void TealCrackedBrick::Init() throw() {

	this->GameObject::Init();
}

void TealCrackedBrick::Terminate() {

	this->GameObject::Terminate();
}

SpriteFace* TealCrackedBrick::CreateSpriteFace() {

	SpriteFace* face = new SpriteFace("Teal Cracked Face");

	face->RegisterFace(SpriteFace::front, "CRACK+TEAL");

	return face;
}

