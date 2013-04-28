#include "lethal_empty_block.h"

LethalEmptyBlock::LethalEmptyBlock() : LethalBlock("LethalEmptyBlock", "LethalEmptyBlock") {

}

LethalEmptyBlock::~LethalEmptyBlock() {
}

void LethalEmptyBlock::Init() throw() {

	w = BrickObject::Width;
	h = BrickObject::Height;

	boundingBox.x = 0;
	boundingBox.y = 0;
	boundingBox.w = w;
	boundingBox.h = h;

	// bypass all the way to GameObject Inits on purpose
	this->BaseSystem::Init();
}

void LethalEmptyBlock::Terminate() {

	this->LethalBlock::Terminate();
}

void LethalEmptyBlock::Render() {
	// Nothing to render.
}

SpriteFace* LethalEmptyBlock::CreateSpriteFace() {

	return NULL;	
}

