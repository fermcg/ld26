#pragma once

#include <SDL2/SDL.h>

#include "base_system.h"
#include "config.h"

class Texture : public BaseSystem {
	public:
		Texture(const char* fileName, const char* textureId);
		~Texture();

		void Init();
		void Terminate();

		SDL_Texture* texture;
		int w;
		int h;
	private:
		string fileName;
};
