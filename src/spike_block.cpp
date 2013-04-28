#include "spike_block.h"

SpikeBlock::SpikeBlock() : LethalBlock("SpikeBlock", "SpikeBlock") {

	boundingBox.x = 1;
	boundingBox.y = 2;
	boundingBox.w = 6;
	boundingBox.h = 6;
}

SpikeBlock::~SpikeBlock() {
}

void SpikeBlock::Init() throw() {

	this->LethalBlock::Init();
}

void SpikeBlock::Terminate() {

	this->LethalBlock::Terminate();
}

SpriteFace* SpikeBlock::CreateSpriteFace() {

	SpriteFace* face = new SpriteFace("Spike Face");

	face->RegisterFace(SpriteFace::front, "SPIKES");

	return face;
}
