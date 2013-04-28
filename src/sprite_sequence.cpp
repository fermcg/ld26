#include "sprite_sequence.h"

SpriteSequence::SpriteSequence(Sprite* sprite) {

	this->sprite = sprite;
	currentFrame = 0;
	renderingMode = SpriteSequence::sequence;
}

SpriteSequence::~SpriteSequence() {

}

void SpriteSequence::RenderCopy(const SDL_Rect* destinyRect) throw() {

	sprite->RenderCopy(destinyRect, currentFrame);

	if(renderingMode == SpriteSequence::sequence) {

		currentFrame++;
		if(currentFrame >= sprite->frames) {

			currentFrame = 0;
		}
	}
}

Sprite* SpriteSequence::GetSprite() {

	return sprite;
}

void SpriteSequence::ResetFrame(const int frame) {

	currentFrame = frame;
}
