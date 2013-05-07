#pragma once

#include <SFML/Audio.hpp>

#include "base_system.h"

class SoundEffect : public BaseSystem {
	public:
		SoundEffect(const char* fileName, const char* soundId);
		~SoundEffect();

		void Init();
		void Terminate();

		void Play();
		void Start();
		void Stop();
	private:
		sf::SoundBuffer *buffer;
		sf::Sound *sound;
		string fileName;
};
