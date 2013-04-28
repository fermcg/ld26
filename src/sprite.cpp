#include <SDL.h>
#include <iostream>
#include "sprite.h"
#include "sprite_sequence.h"
#include "exceptions.h"
#include "macros.h"
#include "singletons.h"

using namespace std;

Sprite::Sprite(const char* spriteId, SDL_Texture* texture, const Sint16 x, const Sint16 y, const Uint16 w, const Uint16 h, const int frames) {

	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = w;
	this->rect.h = h;

	this->texture = texture;
	this->spriteId = spriteId;
	this->frames = frames;
}

Sprite::~Sprite() {

}

void Sprite::RenderCopy(const SDL_Rect* destinyRect, const int frame) throw() {

	SDL_Rect sourceRect = rect;
	sourceRect.x += frame * sourceRect.w;

	int r = SDL_RenderCopy(Singleton::screen->renderer, texture, &sourceRect, destinyRect);
	if(r != 0) {

		cerr << "Error rendering Sprite copy -> " << SDL_GetError() << endl;
		THROWINFO(Exception::BadRender, spriteId.c_str());
	}
}

SpriteSequence* Sprite::InstanceSequence() {

	SpriteSequence* sequence = new SpriteSequence(this);
	return sequence;
}
