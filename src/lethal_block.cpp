#include "lethal_block.h"

LethalBlock::LethalBlock(const char* name, const char* objectId) : BrickObject(name, objectId) {

	lethal = true;
}

LethalBlock::~LethalBlock() {
}

void LethalBlock::Init() throw() {

	this->BrickObject::Init();
}

void LethalBlock::Terminate() {

	this->BrickObject::Terminate();
}
