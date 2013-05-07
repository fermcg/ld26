#pragma once

#include "config.h"
#include "game_system.h"
#include "screen.h"
#include "texture_map.h"
#include "sprite_map.h"
#include "game_panel.h"
#include "sound_effects_map.h"
#include "stage_map.h"
#include "player.h"
#include "game_loop.h"
#include "all_objects.h"

#ifdef SINGLETONS_CPP
#define SINGLETON
#else
#define SINGLETON extern
#endif

namespace Singleton {
	void Init() throw();
	void Terminate();

	SINGLETON Config* config;
	SINGLETON GameSystem* gameSystem;
	SINGLETON Screen* screen;
	SINGLETON TextureMap* textureMap;
	SINGLETON SpriteMap* spriteMap;
	SINGLETON GamePanel* gamePanel;
	SINGLETON SoundEffectsMap* soundEffectsMap;
	SINGLETON StageMap* stageMap;
	SINGLETON AllObjects* allFriends;
//	SINGLETON AllObjects* allEnemies;
	SINGLETON Player* player;
	SINGLETON GameLoop* gameLoop;

	extern bool broken;
}
