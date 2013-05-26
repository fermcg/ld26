#include <iostream>
#include "sprite_map.h"
#include "singletons.h"
#include "macros.h"
#include "exceptions.h"
#include "brick_object.h"

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
//	LoadWalkingCharacter("PLAYER", spritesTexture, sf::IntRect(0, 0, 8, 16));
	// Play as farmer
//	LoadWalkingCharacter("PLAYER", spritesTexture, sf::IntRect(0, 176, 8, 16));
	// Play as dog
	LoadWalkingCharacter("PLAYER", spritesTexture, sf::IntRect(0, 168, 8, 8));

	LoadSprite("PLAYER+SHOT", spritesTexture, sf::IntRect(96, 0, 32, 16), sf::IntRect(0, 0, 8, 8));
	// Scene
	LoadSprite("BRICK+TEAL", spritesTexture, sf::IntRect(24, 40, 8, 8));
	LoadSprite("CRACK+TEAL", spritesTexture, sf::IntRect(48, 16, 8, 8));
	LoadSprite("BRICK+BROWN", spritesTexture, sf::IntRect(24, 32, 8, 8));
	LoadSprite("BRICK+COLORS", spritesTexture, sf::IntRect(24, 56, 8, 8));
	LoadSprite("BRICK+BLINK", spritesTexture, sf::IntRect(32, 48, 16, 16), sf::IntRect(0, 0, 8, 8));
	LoadSprite("BRICK+EARTH", spritesTexture, sf::IntRect(24, 48, 8, 8), sf::IntRect(0, 0, 8, 8));
	LoadSprite("BRICK+GRAY", spritesTexture, sf::IntRect(24, 16, 8, 8), sf::IntRect(0, 0, 8, 8));
	LoadSprite("CRACK+ICE", spritesTexture, sf::IntRect(48, 32, 8, 8));

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
	// New Life
	LoadSprite("NEWLIFE", spritesTexture, sf::IntRect(80, 32, 8, 8));
	// Fill Health
	LoadSprite("PORK", spritesTexture, sf::IntRect(80, 48, 8, 8));
	LoadSprite("TOMATO", spritesTexture, sf::IntRect(88, 48, 8, 8));
	// Health
	LoadSprite("ENERGY+R", spritesTexture, sf::IntRect(0, 72, 80, 8));
	LoadSprite("ENERGY+G", spritesTexture, sf::IntRect(0, 80, 80, 8));

	// Enemies
	LoadSprite("BOUNCER", spritesTexture, sf::IntRect(56, 32, 16, 16), sf::IntRect(0,0,8,8));

	LoadSprite("MOTHERSHIP", spritesTexture, sf::IntRect(0, 192, 32, 16), sf::IntRect(0,0,16,8));
	LoadSprite("MOTHERSHIP+DEATH", spritesTexture, sf::IntRect(32, 192, 16, 16), sf::IntRect(0,0,16,8));

	LoadSprite("ALIEN", spritesTexture, sf::IntRect(0, 208, 16, 16), sf::IntRect(0,0,8,8));
	LoadSprite("ALIEN+DEATH", spritesTexture, sf::IntRect(16, 208, 8, 16), sf::IntRect(0,0,8,8));
	LoadSprite("ALIEN+SHOT", spritesTexture, sf::IntRect(24, 208, 8, 16), sf::IntRect(0,0,8,8));

	LoadWalkingCharacter("DOG", spritesTexture, sf::IntRect(0, 168, 8, 8));

	LoadWalkingCharacter("FARMER", spritesTexture, sf::IntRect(0, 176, 8, 16));

	//	LoadSprite("ENEMY", spritesTexture, sf::IntRect(0, 64, 32, 32), 4);
	//	LoadSprite("ENEMY+SHOT", spritesTexture, sf::IntRect(0, 96, 32, 32), 4);

	LoadSprite("LIFE", spritesTexture, sf::IntRect(80,32,8,8));
	LoadSprite("CHAR+L+X", spritesTexture, sf::IntRect(40,96, 8, 8));

	LoadSmartBricks("SMART+ICE", spritesTexture, sf::Vector2u(0, 128));
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

void SpriteMap::LoadWalkingCharacter(const char* prefixId, Texture* texture,
									 const sf::IntRect& firstRect) {

	string characterId = prefixId;
	characterId += "+";

	sf::IntRect rect = firstRect;
	sf::IntRect unitRect = firstRect;

	unitRect.left = 0;
	unitRect.top = 0;

	rect.width = 4 * firstRect.width;
	LoadSprite((characterId + "RIGHT").c_str(), texture, rect, unitRect);
	rect.left += rect.width;
	LoadSprite((characterId + "LEFT").c_str(), texture, rect, unitRect);
	rect.left += rect.width;
	rect.width = firstRect.width;
	sf::IntRect deathRect = rect;
	LoadSprite((characterId + "FRONT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "ALT+FRONT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "ALT+RIGHT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "ALT+LEFT").c_str(), texture, rect);

	deathRect.width = 2 * firstRect.width;
	LoadSprite((characterId + "DEATH").c_str(), texture, deathRect, unitRect);
}
void SpriteMap::LoadSmartBricks(const char* prefixId, Texture* texture,
								const sf::Vector2u& position) {
	string characterId = prefixId;
	characterId += "+";

	sf::IntRect rect;

	rect.left = position.x;
	rect.top = position.y;

	rect.width = BrickObject::Width;
	rect.height = BrickObject::Height;

	LoadSprite((characterId + "TLEFT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "UP").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "TRIGHT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "FUP").c_str(), texture, rect);
	rect.left = position.x;
	rect.top += rect.height;

	LoadSprite((characterId + "LEFT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "FRONT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "RIGHT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "VERTICAL").c_str(), texture, rect);
	rect.left = position.x;
	rect.top += rect.height;

	LoadSprite((characterId + "BLEFT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "DOWN").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "BRIGHT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "FDOWN").c_str(), texture, rect);
	rect.left = position.x;
	rect.top += rect.height;

	LoadSprite((characterId + "FLEFT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "HORIZONTAL").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "FRIGHT").c_str(), texture, rect);
	rect.left += rect.width;
	LoadSprite((characterId + "FFRONT").c_str(), texture, rect);
}