#pragma once

#include <SDL2/SDL.h>
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

		Sprite* Get(const char* spriteId) throw();
	private:
		void LoadSprite(const char* spriteId, const Texture* texture,
				const Sint16 x, const Sint16 y,
				const Uint16 w, const Uint16 h, const int frames);
};
