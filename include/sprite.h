#pragma once

#include <SDL.h>
#include <string>

using namespace std;

class SpriteSequence;

class Sprite {
public:

	Sprite(const char* spriteId, SDL_Texture* texture, const Sint16 x, const Sint16 y, const Uint16 w, const Uint16 h, const int frames);
	~Sprite();
	
	void RenderCopy(const SDL_Rect* destinyRect, const int frame) throw();
	SpriteSequence* InstanceSequence();
	
	
	friend class SpriteSequence;
	friend class GameObject;
protected:
	SDL_Rect rect;
	int frames;
			
private:
	SDL_Texture* texture;
	string spriteId;
};
