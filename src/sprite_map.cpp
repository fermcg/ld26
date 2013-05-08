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
	LoadSprite("MENU", menuTexture, sf::IntRect(0, 0, 640, 480), 1);
	// Sprites from "SPRITES" texture map.
	// This could be loaded from a file or resource...
	Texture* spritesTexture = Singleton::textureMap->Get("SPRITES");
	LoadSprite("PLAYER+RIGHT", spritesTexture, sf::IntRect(0, 0, 8, 16), 4);
	LoadSprite("PLAYER+LEFT", spritesTexture, sf::IntRect(32, 0, 8, 16), 4);
	LoadSprite("PLAYER+FRONT", spritesTexture, sf::IntRect(64, 0, 8, 16), 1);
	LoadSprite("PLAYER+JUMP+RIGHT", spritesTexture, sf::IntRect(72, 0, 8, 16), 1);
	LoadSprite("PLAYER+JUMP+LEFT", spritesTexture, sf::IntRect(80, 0, 8, 16), 1);
	LoadSprite("PLAYER+JUMP+FRONT", spritesTexture, sf::IntRect(88, 0, 8, 16), 1);
	LoadSprite("PLAYER+SHOT", spritesTexture, sf::IntRect(32, 16, 8, 8), 8);
	// Scene
	LoadSprite("BRICK+TEAL", spritesTexture, sf::IntRect(0, 16, 8, 8), 2);
	LoadSprite("CRACK+TEAL", spritesTexture, sf::IntRect(0, 24, 8, 8), 2);
	LoadSprite("BRICK+BROWN", spritesTexture, sf::IntRect(16, 24, 8, 8), 1);
	LoadSprite("BRICK+COLORS", spritesTexture, sf::IntRect(24, 24, 8, 8), 1);
	LoadSprite("BRICK+BLINK", spritesTexture, sf::IntRect(32, 24, 8, 8), 4);
	LoadSprite("BRICK+EARTH", spritesTexture, sf::IntRect(64, 24, 8, 8), 2);
	
	LoadSprite("MUSHROOM+LEFT", spritesTexture, sf::IntRect(80, 24, 8, 8), 1);
	LoadSprite("MUSHROOM+TOP", spritesTexture, sf::IntRect(88, 24, 8, 8), 1);
	LoadSprite("MUSHROOM+RIGHT", spritesTexture, sf::IntRect(96, 24, 8, 8), 1);
	LoadSprite("MUSHROOM+JUNCTION", spritesTexture, sf::IntRect(80, 32, 8, 8), 1);
	LoadSprite("MUSHROOM+TRUNK", spritesTexture, sf::IntRect(88, 32, 8, 8), 1);
	LoadSprite("MUSHROOM+ROOT", spritesTexture, sf::IntRect(96, 32, 8, 8), 1);

	LoadSprite("TREE+LEFT", spritesTexture, sf::IntRect(80, 40, 8, 8), 1);
	LoadSprite("TREE+TOP", spritesTexture, sf::IntRect(88, 40, 8, 8), 1);
	LoadSprite("TREE+RIGHT", spritesTexture, sf::IntRect(96, 40, 8, 8), 1);
	LoadSprite("TREE+JUNCTION", spritesTexture, sf::IntRect(80, 48, 8, 8), 1);
	LoadSprite("TREE+TRUNK", spritesTexture, sf::IntRect(88, 48, 8, 8), 1);
	LoadSprite("TREE+ROOT", spritesTexture, sf::IntRect(96, 48, 8, 8), 1);

	LoadSprite("SPIKES+UP", spritesTexture, sf::IntRect(16, 16, 8, 8), 1);
	LoadSprite("SPIKES+DOWN", spritesTexture, sf::IntRect(24, 16, 8, 8), 1);
	LoadSprite("DOOR+CLOSED", spritesTexture, sf::IntRect(96, 0, 8, 16), 1);
	LoadSprite("DOOR+OPENED", spritesTexture, sf::IntRect(104, 0, 8, 16), 1);
	// Numbers
	LoadSprite("NUMBERS+R", spritesTexture, sf::IntRect(0, 32, 8, 8), 10);
	LoadSprite("NUMBERS+G", spritesTexture, sf::IntRect(0, 40, 8, 8), 10);
	LoadSprite("NUMBERS+B", spritesTexture, sf::IntRect(0, 48, 8, 8), 10);
	// Health
	LoadSprite("ENERGY+R", spritesTexture, sf::IntRect(0, 56, 80, 4), 1);
	LoadSprite("ENERGY+G", spritesTexture, sf::IntRect(0, 60, 80, 4), 1);

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

void SpriteMap::LoadSprite(const char* spriteId, const Texture* texture, const sf::IntRect& rect, const int frames) {

	SpriteMap::const_iterator it;
	it = this->find(spriteId);
	if(it != this->end()) {

		cerr << "Invalid sprite object -> [" << spriteId << "] sprite already loaded.";
		THROWINFO(Exception::BadObject, spriteId);		
	}

	if(rect.left + frames * rect.width > texture->w || rect.top + rect.height > texture->h) {

		cerr << "Invalid sprite object dimensions -> "
			<< "[x:" << rect.left << " y:" << rect.top << " w:" << rect.width << " h:" << rect.height << "]"
			<< " in a texture of "
			<< "[w:" << texture->w << " h:" << texture->h << "]" << endl;
		THROWINFO(Exception::BadObject, spriteId);
	}

	Sprite* sprite = new Sprite(spriteId, texture->texture, rect, frames);
	(*this)[spriteId] = sprite;
}
