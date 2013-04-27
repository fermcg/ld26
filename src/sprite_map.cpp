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
	
	// Sprites from "SPRITES" texture map.
	// This could be loaded from a file or resource...
	Texture* spritesTexture = Singleton::textureMap->Get("SPRITES");
	LoadSprite("PLAYER+RIGHT", spritesTexture, 0, 0, 8, 16, 4);
	LoadSprite("PLAYER+LEFT", spritesTexture, 32, 0, 8, 16, 4);
	LoadSprite("PLAYER+FRONT", spritesTexture, 64, 0, 8, 16, 1);
	LoadSprite("PLAYER+JUMP+RIGHT", spritesTexture, 80, 0, 8, 16, 1);
	LoadSprite("PLAYER+JUMP+LEFT", spritesTexture, 96, 0, 8, 16, 1);
	LoadSprite("PLAYER+JUMP+FRONT", spritesTexture, 112, 0, 8, 16, 1);
	// Scene
	LoadSprite("BRICK+TEAL", spritesTexture, 0, 16, 8, 8, 2);
//	LoadSprite("PLAYER+SHOT", spritesTexture, 0, 32, 32, 32, 4);
//	LoadSprite("ENEMY", spritesTexture, 0, 64, 32, 32, 4);
//	LoadSprite("ENEMY+SHOT", spritesTexture, 0, 96, 32, 32, 4);
}

void SpriteMap::Terminate() {

	SpriteMap::iterator it;
	for(it = this->begin(); it != this->end(); it++) {
		
		delete it->second;
	}
	this->clear();
	this->BaseSystem::Terminate();

}

Sprite* SpriteMap::Get(const char* spriteId) {
	
	SpriteMap::iterator it;
	it = this->find(spriteId);
	if(it == this->end()) {
		
		cerr << "Error getting [" << spriteId << "] sprite" << endl;
		THROWINFO(Exception::SpriteNotFound, spriteId);
	}
	
	return it->second;
}

void SpriteMap::LoadSprite(const char* spriteId, const Texture* texture, const Sint16 x, const Sint16 y, const Uint16 w, const Uint16 h, const int frames) {
	
	SpriteMap::const_iterator it;
	it = this->find(spriteId);
	if(it != this->end()) {
		
		cerr << "Invalid sprite object -> [" << spriteId << "] sprite already loaded.";
		THROWINFO(Exception::BadObject, spriteId);		
	}
	
	if(x + frames * w > texture->w || y + h > texture->h) {
		
		cerr << "Invalid sprite object dimensions -> "
			<< "[x:" << x << " y:" << y << " w:" << w << " h:" << h << "]"
			<< " in a texture of "
			<< "[w:" << texture->w << " h:" << texture->h << "]" << endl;
		THROWINFO(Exception::BadObject, spriteId);
	}
	
	Sprite* sprite = new Sprite(spriteId, texture->texture, x, y, w, h, frames);
	(*this)[spriteId] = sprite;
}
