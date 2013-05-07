#pragma once

#include <SFML/Graphics.hpp>

#include "base_system.h"
#include "config.h"

class Texture : public BaseSystem {
	public:
		Texture(const char* fileName, const char* textureId);
		~Texture();

		void Init();
		void Terminate();

		sf::Texture* texture;
		int w;
		int h;
	private:
		string fileName;
};
