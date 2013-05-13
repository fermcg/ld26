#include <iostream>
#include "sprite_map.h"
#include "singletons.h"
#include "macros.h"
#include "exceptions.h"

using namespace std;

SpriteMap::SpriteMap() : BaseSystem("SpriteMap") {

}

SpriteMap::~SpriteMap() {

}

void SpriteMap::Init() {

	this->BaseSystem::Init();

	Texture* menuTexture = Singleton::textureMap->Get("MENU");
	LoadSprite("MENU", menuTexture, sf::IntRect(0, 0, Singleton::screen->window->getSize().x, Singleton::screen->window->getSize().y));
	// Sprites from "SPRITES" texture map.
	// This could be loaded from a file or resource...
	Texture* spritesTexture = Singleton::textureMap->Get("SPRITES");
	LoadSprite("PLAYER+RIGHT", spritesTexture, sf::IntRect(0, 0, 32, 16), sf::IntRect(0, 0, 8, 16));
	LoadSprite("PLAYER+LEFT", spritesTexture, sf::IntRect(32, 0, 32, 16), sf::IntRect(0, 0, 8, 16));
	LoadSprite("PLAYER+FRONT", spritesTexture, sf::IntRect(64, 0, 8, 16));
	LoadSprite("PLAYER+JUMP+RIGHT", spritesTexture, sf::IntRect(72, 0, 8, 16));
	LoadSprite("PLAYER+JUMP+LEFT", spritesTexture, sf::IntRect(80, 0, 8, 16));
	LoadSprite("PLAYER+JUMP+FRONT", spritesTexture, sf::IntRect(88, 0, 8, 16));
	LoadSprite("PLAYER+SHOT", spritesTexture, sf::IntRect(96, 0, 32, 16), sf::IntRect(0, 0, 8, 8));
	// Scene
	LoadSprite("BRICK+TEAL", spritesTexture, sf::IntRect(24, 40, 8, 8));
	LoadSprite("CRACK+TEAL", spritesTexture, sf::IntRect(48, 16, 8, 8));
	LoadSprite("BRICK+BROWN", spritesTexture, sf::IntRect(24, 32, 8, 8));
	LoadSprite("BRICK+COLORS", spritesTexture, sf::IntRect(24, 56, 8, 8));
	LoadSprite("BRICK+BLINK", spritesTexture, sf::IntRect(32, 48, 16, 16), sf::IntRect(0, 0, 8, 8));
	LoadSprite("BRICK+EARTH", spritesTexture, sf::IntRect(24, 48, 8, 8), sf::IntRect(0, 0, 8, 8));
	LoadSprite("BRICK+GRAY", spritesTexture, sf::IntRect(24, 16, 8, 8), sf::IntRect(0, 0, 8, 8));
	
	LoadSprite("MUSHROOM+LEFT", spritesTexture, sf::IntRect(104, 72, 8, 8));
	LoadSprite("MUSHROOM+TOP", spritesTexture, sf::IntRect(112, 72, 8, 8));
	LoadSprite("MUSHROOM+RIGHT", spritesTexture, sf::IntRect(120, 72, 8, 8));
	LoadSprite("MUSHROOM+JUNCTION", spritesTexture, sf::IntRect(104, 80, 8, 8));
	LoadSprite("MUSHROOM+TRUNK", spritesTexture, sf::IntRect(112, 80, 8, 8));
	LoadSprite("MUSHROOM+ROOT", spritesTexture, sf::IntRect(120, 80, 8, 8));

	LoadSprite("TREE+LEFT", spritesTexture, sf::IntRect(104, 56, 8, 8));
	LoadSprite("TREE+TOP", spritesTexture, sf::IntRect(112, 56, 8, 8));
	LoadSprite("TREE+RIGHT", spritesTexture, sf::IntRect(120, 56, 8, 8));
	LoadSprite("TREE+JUNCTION", spritesTexture, sf::IntRect(104, 64, 8, 8));
	LoadSprite("TREE+TRUNK", spritesTexture, sf::IntRect(112, 64, 8, 8));
	LoadSprite("TREE+ROOT", spritesTexture, sf::IntRect(120, 64, 8, 8));

	LoadSprite("SPIKES+UP", spritesTexture, sf::IntRect(96, 32, 8, 8));
	LoadSprite("SPIKES+DOWN", spritesTexture, sf::IntRect(96, 40, 8, 8));
	LoadSprite("DOOR+CLOSED", spritesTexture, sf::IntRect(112, 32, 8, 16));
	LoadSprite("DOOR+OPENED", spritesTexture, sf::IntRect(120, 32, 8, 16));
	// Numbers
	LoadSprite("NUMBERS+W", spritesTexture, sf::IntRect(48, 96, 80, 8), sf::IntRect(0, 0, 8, 8));
	LoadSprite("NUMBERS+R", spritesTexture, sf::IntRect(48, 104, 80, 8), sf::IntRect(0, 0, 8, 8));
	LoadSprite("NUMBERS+G", spritesTexture, sf::IntRect(48, 112, 80, 8), sf::IntRect(0, 0, 8, 8));
	LoadSprite("NUMBERS+B", spritesTexture, sf::IntRect(48, 120, 80, 8), sf::IntRect(0, 0, 8, 8));
	// Health
	LoadSprite("ENERGY+R", spritesTexture, sf::IntRect(0, 72, 80, 8));
	LoadSprite("ENERGY+G", spritesTexture, sf::IntRect(0, 80, 80, 8));

	// Bouncer
	LoadSprite("BOUNCER", spritesTexture, sf::IntRect(56, 32, 16, 16), sf::IntRect(0,0,8,8));
	//	LoadSprite("ENEMY", spritesTexture, sf::IntRect(0, 64, 32, 32), 4);
	//	LoadSprite("ENEMY+SHOT", spritesTexture, sf::IntRect(0, 96, 32, 32), 4);
}

void SpriteMap::Terminate() {

	SpriteMap::iterator it;
	for(it = this->begin(); it != this->end(); it++) {

		delete it->second;
	}
	this->clear();
	this->BaseSystem::Terminate();

}

Sprite* SpriteMap::Get(const char* spriteId) throw() {

	SpriteMap::iterator it;
	it = this->find(spriteId);
	if(it == this->end()) {

		cerr << "Error getting [" << spriteId << "] sprite" << endl;
		THROWINFO(Exception::SpriteNotFound, spriteId);
	}

	return it->second;
}

void SpriteMap::LoadSprite(const char* spriteId, Texture* texture,
						   const sf::IntRect& rect) {
	sf::IntRect sRect = rect;

	sRect.left = 0;
	sRect.top = 0;

	LoadSprite( spriteId, texture, rect, sRect);
}
void SpriteMap::LoadSprite(const char* spriteId, Texture* texture,
						   const sf::IntRect& rect, const sf::IntRect& sRect) {

	SpriteMap::const_iterator it;
	it = this->find(spriteId);
	if(it != this->end()) {

		cerr << "Invalid sprite object -> [" << spriteId << "] sprite already loaded.";
		THROWINFO(Exception::BadObject, spriteId);		
	}

	if(rect.left + rect.width > texture->w || rect.top + rect.height > texture->h) {

		cerr << "Invalid sprite object dimensions -> "
			<< "[x:" << rect.left << " y:" << rect.top << " w:" << rect.width << " h:" << rect.height << "]"
			<< " in a texture of "
			<< "[w:" << texture->w << " h:" << texture->h << "]" << endl;
		THROWINFO(Exception::BadObject, spriteId);
	}

	Sprite* sprite = new Sprite(spriteId, texture, rect, sRect);
	(*this)[spriteId] = sprite;
}
