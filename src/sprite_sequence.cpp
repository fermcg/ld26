#include "sprite_sequence.h"

SpriteSequence::SpriteSequence(Sprite* sprite) {

	this->sprite = sprite;
	currentFrame = 0;
	locked = false;
	renderingMode = SpriteSequence::sequence;
}

SpriteSequence::~SpriteSequence() {

}

void SpriteSequence::RenderCopy(const SDL_Rect* destinyRect) throw() {

	sprite->RenderCopy(destinyRect, currentFrame);

	if(renderingMode == SpriteSequence::sequence && !locked) {
		IncrementSequence();
	}
}

Sprite* SpriteSequence::GetSprite() {

	return sprite;
}

void SpriteSequence::ResetFrame(const int frame) {

	currentFrame = frame;
}

void SpriteSequence::LockSequence() {

	locked = true;
}

void SpriteSequence::UnlockSequence() {

	locked = false;
}

void SpriteSequence::IncrementSequence() {
	currentFrame++;
	if(currentFrame >= sprite->frames) {

		currentFrame = 0;
	}
}

void SpriteSequence::SetRenderingMode(const RenderingMode renderingMode) {

	this->renderingMode = renderingMode;
}
