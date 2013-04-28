#pragma once

#include <map>

#include "base_system.h"
#include "texture.h"

using namespace std;

class TextureMap : public BaseSystem, map< string, Texture* > {
	public:
		TextureMap();
		~TextureMap();

		void Init();
		void Terminate();

		Texture* Get(const char* textureId);
	private:
		void LoadFile(const char* textureId, const char* path);
};
