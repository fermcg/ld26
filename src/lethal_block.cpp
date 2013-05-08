#include "lethal_block.h"

LethalBlock::LethalBlock(const char* name, const char* objectId) : BrickObject(name, objectId) {

	lethal = true;
	damage = 10000;
	solid = false;
	scoreValue = 1000;
}

LethalBlock::~LethalBlock() {
}

void LethalBlock::Init() throw() {

	this->BrickObject::Init();
}

void LethalBlock::Terminate() {

	this->BrickObject::Terminate();
}
