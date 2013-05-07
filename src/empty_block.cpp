#include "empty_block.h"

EmptyBlock::EmptyBlock() : BrickObject("EmptyBlock", "EmptyBlock") {
}

EmptyBlock::~EmptyBlock() {
}

void EmptyBlock::Init() throw() {

	w = BrickObject::Width;
	h = BrickObject::Height;

	boundingBox.left = 0;
	boundingBox.top = 0;
	boundingBox.width= w;
	boundingBox.height = h;

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
