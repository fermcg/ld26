#include "spike_block.h"

SpikeBlock::SpikeBlock() : LethalBlock("SpikeBlock", "SpikeBlock") {

	boundingBox.left = 1;
	boundingBox.top = 2;
	boundingBox.width = 6;
	boundingBox.height = 4;
	
	preRender = true;
	mirrored = true;
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

	face->RegisterFace(SpriteFace::up, "SPIKES+UP");
	face->RegisterFace(SpriteFace::down, "SPIKES+DOWN");
	
	face->ChangeFace(SpriteFace::up);

	return face;
}
