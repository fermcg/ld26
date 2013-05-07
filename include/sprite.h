#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class SpriteSequence;

class Sprite {
	public:

		Sprite(const char* spriteId, sf::Texture* texture, const sf::IntRect& rect, const int frames);
		~Sprite();

		void RenderCopy(const sf::IntRect* destinyRect = NULL, const int frame = 0) throw();
		SpriteSequence* InstanceSequence();


		friend class SpriteSequence;
		friend class GameObject;
		friend class GamePanel;
		sf::IntRect rect;
		string spriteId;
	protected:
		int frames;

	private:
		sf::Sprite sprite;
		sf::Texture* texture;
};
