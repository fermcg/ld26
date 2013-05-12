#include "sprite_sequence.h"

SpriteSequence::SpriteSequence(Sprite* sprite) {

	this->sprite = sprite;
	currentFrame = 0;
	locked = false;
	renderingMode = SpriteSequence::sequence;
	counter = 0;
	counterTarget = 1;
}

SpriteSequence::~SpriteSequence() {

}

void SpriteSequence::RenderCopy(const sf::IntRect* destinyRect) throw() {

	sprite->RenderCopy(destinyRect, currentFrame);

	if(renderingMode == SpriteSequence::sequence && !locked) {
		IncrementSequence();
	}
}

void SpriteSequence::RenderToImage(sf::Image& destinyImage,
								   const int x, const int y,
								   const int frame) throw() {
	
	sprite->RenderToImage(destinyImage, x, y, frame);
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
	counter++;
	if (counter < counterTarget) {
		
		return;
	}
	counter = 0;
	currentFrame++;
	if(currentFrame >= sprite->frames) {

		currentFrame = 0;
	}
}

void SpriteSequence::SetRenderingMode(const RenderingMode renderingMode) {

	this->renderingMode = renderingMode;
}
