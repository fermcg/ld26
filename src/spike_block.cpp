#include "spike_block.h"

SpikeBlock::SpikeBlock() : LethalBlock("SpikeBlock", "SpikeBlock") {

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
