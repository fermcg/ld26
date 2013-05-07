#pragma once

#include <SDL2/SDL.h>
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

		void LockSequence();
		void UnlockSequence();
		void IncrementSequence();

		void SetRenderingMode(const RenderingMode renderingMode);

	protected:
		int currentFrame;
		bool locked;
		Sprite* sprite;
		RenderingMode renderingMode;	
};
