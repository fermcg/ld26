#pragma once

#include <SFML/Graphics.hpp>
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
		void LoadSprite(const char* spriteId, Texture* texture,
						const sf::IntRect& rect);
		void LoadSprite(const char* spriteId, Texture* texture,
						const sf::IntRect& rect, const sf::IntRect& sRect);
		void LoadSmartBricks(const char* prefixId, Texture* texture,
							 const sf::Vector2u position);
};
