#pragma once

#include <map>

#include "base_system.h"
#include "sound_effect.h"
#include "sprite.h"

using namespace std;

class SoundEffectsMap : public BaseSystem, map< string, SoundEffect* > {
	public:
		SoundEffectsMap();
		~SoundEffectsMap();

		void Init();
		void Terminate();

		SoundEffect* Get(const char* soundId);
	private:
		void LoadSound(const char* soundId, const char* fileName);
};
