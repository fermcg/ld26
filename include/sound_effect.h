#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

#include "base_system.h"

class SoundEffect : public BaseSystem {
public:
	SoundEffect(const char* fileName, const char* soundId);
	~SoundEffect();

	void Init();
	void Terminate();

	int Play(const int channelId = -1, const int loops = 0);
	int Start(const int channelId);
	void Stop(const int channelId);
private:
	Mix_Chunk *sample;
	string fileName;
};
