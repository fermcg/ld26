#pragma once

#include <SDL.h>
#include "sprite.h"

using namespace std;

class SpriteSequence {
public:
	enum RenderingMode {
		single_frame = 0,
		sequence
	};
	
	SpriteSequence(Sprite* sprite);
	~SpriteSequence();
	
	void RenderCopy(const SDL_Rect* destinyRect) throw();
	Sprite* GetSprite();
	void ResetFrame(const int frame = 0);

protected:
	int currentFrame;
	Sprite* sprite;
	RenderingMode renderingMode;	
};