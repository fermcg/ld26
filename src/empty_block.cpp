#include "empty_block.h"

EmptyBlock::EmptyBlock() : BrickObject("EmptyBlock", "EmptyBlock") {
}

EmptyBlock::~EmptyBlock() {
}

void EmptyBlock::Init() throw() {

	w = BrickObject::Width;
	h = BrickObject::Height;

	boundingBox.x = 0;
	boundingBox.y = 0;
	boundingBox.w = w;
	boundingBox.h = h;

	// bypass all the way to GameObject Inits on purpose
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
