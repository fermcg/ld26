#pragma once

#include <SDL.h>
#include <map>

#include "base_system.h"
#include "texture.h"
#include "sprite.h"

using namespace std;

class SpriteMap : public BaseSystem, map< string, Sprite* > {
public:
	SpriteMap();
	~SpriteMap();

	void Init();
	void Terminate();
	
	Sprite* Get(const char* spriteId);
private:
	void LoadSprite(const char* name, const Texture* texture,
	 				const Sint16 x, const Sint16 y,
	 				const Uint16 w, const Uint16 h, const int frames);
};
