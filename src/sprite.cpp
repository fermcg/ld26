#include <iostream>
#include "sprite.h"
#include "sprite_sequence.h"
#include "exceptions.h"
#include "macros.h"
#include "singletons.h"

using namespace std;

Sprite::Sprite(const char* spriteId, Texture* texture,
			   const sf::IntRect& rect, const sf::IntRect& sRect) {

	this->rect = rect;
	this->sRect = sRect;

	this->texture = texture;
	this->sfTexture = texture->texture;
	this->spriteId = spriteId;
	this->xFrames = (rect.width / sRect.width);
	this->yFrames = (rect.height / sRect.height);

	this->frames = this->xFrames * this->yFrames;
	sprite.setTexture(*sfTexture);
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

	sprite.setTexture(*sfTexture);
	sprite.setTextureRect(sourceRect);

	if (!destinyRect) {

		sprite.setPosition(0.0, 0.0);
	} else {

		sprite.setPosition((float)destinyRect->left, (float)destinyRect->top);
	}

	Singleton::screen->window->draw(sprite);
}

void Sprite::RenderToImage(sf::Image& destinyImage, const int x, const int y,
						   const int frame) throw() {
	
	sf::IntRect sourceRect;
	
	int fx = frame % xFrames;
	int fy = frame / xFrames;
	
	sourceRect.left = rect.left + fx * sRect.width;
	sourceRect.top = rect.top + fy * sRect.height;
	sourceRect.width = sRect.width;
	sourceRect.height = sRect.height;
				
	destinyImage.copy(texture->image, x, y, sourceRect);
}

SpriteSequence* Sprite::InstanceSequence() {

	SpriteSequence* sequence = new SpriteSequence(this);
	return sequence;
}
