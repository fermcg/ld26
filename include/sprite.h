#pragma once

#include "texture.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class SpriteSequence;

class Sprite {
public:

	Sprite(const char* spriteId, Texture* texture,
		   const sf::IntRect& rect, const sf::IntRect& sRect);
	~Sprite();

	void RenderCopy(const sf::IntRect* destinyRect = NULL,
					const int frame = 0) throw();
	void RenderToImage(sf::Image& destinyImage, const int x, const int y,
					   const int frame = 0) throw();
	
	SpriteSequence* InstanceSequence();

	friend class SpriteSequence;
	friend class GameObject;
	friend class GamePanel;
	sf::IntRect rect;
	sf::IntRect sRect;
	string spriteId;
protected:
	int xFrames;
	int yFrames;
	int frames;

private:
	sf::Sprite sprite;
	Texture* texture;
	sf::Texture* sfTexture;
};
