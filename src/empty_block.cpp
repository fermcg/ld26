#include "empty_block.h"

EmptyBlock::EmptyBlock() : BrickObject("EmptyBrick", "EmptyBrick") {
}

EmptyBlock::~EmptyBlock() {
}

void EmptyBlock::Init() throw() {

	w = BrickObject::Width;
	h = BrickObject::Height;
	
	this->BaseSystem::Init();
}

void EmptyBlock::Terminate() {

	this->BrickObject::Terminate();
}

void EmptyBlock::Render() {
	// Nothing to render.
}

SpriteFace* EmptyBlock::CreateSpriteFace() {

	return NULL;	
}
