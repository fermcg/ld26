#pragma once

#include <SDL.h>
#include <string>

using namespace std;

class Sprite {
public:
	enum RenderingMode {
		single_frame = 0,
		sequence
	};
	
	Sprite(const char* spriteId, SDL_Texture* texture, const Sint16 x, const Sint16 y, const Uint16 w, const Uint16 h, const int frames);
	~Sprite();
	
	void RenderCopy(const SDL_Rect* destinyRect) throw();
	void RenderCopy(const SDL_Rect* destinyRect, const int frame) throw();
	
	friend class GameObject;
protected:
	SDL_Rect rect;
	RenderingMode renderingMode;
	int currentFrame;
			
private:
	SDL_Texture* texture;
	string spriteId;
	int frames;
};
