#pragma once

#include <SFML/Graphics.hpp>
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

		void RenderCopy(const sf::IntRect* destinyRect) throw();
		Sprite* GetSprite();
		void ResetFrame(const int frame = 0);

		void LockSequence();
		void UnlockSequence();
		void IncrementSequence();

		void SetRenderingMode(const RenderingMode renderingMode);

		int counterTarget;
	
	protected:
		int currentFrame;
		int counter;
		bool locked;
		Sprite* sprite;
		RenderingMode renderingMode;	
};
