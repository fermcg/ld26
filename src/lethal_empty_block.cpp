#include "lethal_empty_block.h"

LethalEmptyBlock::LethalEmptyBlock() : LethalBlock("LethalEmptyBlock", "LethalEmptyBlock") {

}

LethalEmptyBlock::~LethalEmptyBlock() {
}

void LethalEmptyBlock::Init() throw() {

	w = BrickObject::Width;
	h = BrickObject::Height;

	boundingBox.left = 0;
	boundingBox.top = 0;
	boundingBox.width = w;
	boundingBox.height = h;

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

