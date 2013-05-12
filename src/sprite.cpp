#include <iostream>
#include "sprite.h"
#include "sprite_sequence.h"
#include "exceptions.h"
#include "macros.h"
#include "singletons.h"

using namespace std;

Sprite::Sprite(const char* spriteId, sf::Texture* texture,
			   const sf::IntRect& rect, const sf::IntRect& sRect) 
: sprite(*texture) {

	this->rect = rect;
	this->sRect = sRect;

	this->texture = texture;
	this->spriteId = spriteId;
	this->xFrames = (rect.width / sRect.width);
	this->yFrames = (rect.height / sRect.height);

	this->frames = this->xFrames * this->yFrames;
}

Sprite::~Sprite() {

}

void Sprite::RenderCopy(const sf::IntRect* destinyRect, const int frame) throw() {

	sf::IntRect sourceRect;
	
	int fx = frame % xFrames;
	int fy = frame / xFrames;

	sourceRect.left = rect.left + fx * sRect.width;
	sourceRect.top = rect.top + fy * sRect.height;
	sourceRect.width = sRect.width;
	sourceRect.height = sRect.height;

	sprite.setTexture(*texture);
	sprite.setTextureRect(sourceRect);

	if (!destinyRect) {

		sprite.setPosition(0.0, 0.0);
	} else {

		sprite.setPosition((float)destinyRect->left, (float)destinyRect->top);
	}

	Singleton::screen->window->draw(sprite);
}

SpriteSequence* Sprite::InstanceSequence() {

	SpriteSequence* sequence = new SpriteSequence(this);
	return sequence;
}
