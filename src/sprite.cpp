#include <iostream>
#include "sprite.h"
#include "sprite_sequence.h"
#include "exceptions.h"
#include "macros.h"
#include "singletons.h"

using namespace std;

Sprite::Sprite(const char* spriteId, sf::Texture* texture, const sf::IntRect& rect, const int frames) 
: sprite(*texture) {

	this->rect = rect;

	this->texture = texture;
	this->spriteId = spriteId;
	this->frames = frames;
}

Sprite::~Sprite() {

}

void Sprite::RenderCopy(const sf::IntRect* destinyRect, const int frame) throw() {

	sf::IntRect sourceRect = rect;
	sourceRect.left += frame * sourceRect.width;

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
