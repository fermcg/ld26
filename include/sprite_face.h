#pragma once

#include <map>
#include <SDL.h>

#include "base_system.h"
#include "sprite_sequence.h"

using namespace std;

class SpriteFace : public BaseSystem {
	public:
		enum Facing {
			front = 0,
			left,
			right,
			jumping_front,
			jumping_left,
			jumping_right,
			opened,
			closed
		};
		SpriteFace(const char* objectId);
		~SpriteFace();

		void Init();
		void Terminate();

		void RenderCopy(const SDL_Rect* destinyRect) throw();
		SpriteSequence* GetSequence() throw();

		void RegisterFace(const Facing facing, const char* spriteId) throw();
		//SpriteSequence* spriteSequence);
		void ChangeFace(const Facing facing);

		typedef map<Facing, SpriteSequence*> MapOfFaces;

	protected:
		MapOfFaces faces;
		Facing facing;
};
