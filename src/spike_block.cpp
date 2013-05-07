#include "spike_block.h"

SpikeBlock::SpikeBlock() : LethalBlock("SpikeBlock", "SpikeBlock") {

	boundingBox.left = 1;
	boundingBox.top = 2;
	boundingBox.width = 6;
	boundingBox.height = 6;
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
