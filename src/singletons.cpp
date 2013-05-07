#define SINGLETONS_CPP
#include <iostream>
#include <sstream>

#include "singletons.h"
#include "exceptions.h"
#include "macros.h"

using namespace std;

namespace Singleton {

	bool initialized = false;
	bool broken = false;

	void Init() throw() {

		if (initialized) {

			cerr << "Singleton::Init - called after initializing" << endl;
			THROWINFO(Exception::ShouldNotBeReached, "Singleton");
		}

		config = NULL;
		gameSystem = NULL;
		screen = NULL;
		textureMap = NULL;
		spriteMap = NULL;
		gamePanel = NULL;
		soundEffectsMap = NULL;
		allFriends = NULL;
		//allEnemies = NULL;
		player = NULL;
		gameLoop = NULL;

		broken = true; // Until initializes everything - we will consider it broken.

		config = new Config("game.cfg");
		gameSystem = new GameSystem();
		screen = new Screen();
		textureMap = new TextureMap();
		spriteMap = new SpriteMap();
		gamePanel = new GamePanel();
		soundEffectsMap = new SoundEffectsMap();
		stageMap = new StageMap();
		allFriends = new AllObjects();
		//allEnemies = new AllObjects();
		player = new Player();
		gameLoop = new GameLoop();

		config->Init();
		gameSystem->Init();
		screen->Init();
		textureMap->Init();
		spriteMap->Init();
		gamePanel->Init();
		soundEffectsMap->Init();
		stageMap->Init();
		allFriends->Init();
		//allEnemies->Init();
		player->Init();
		gameLoop->Init();

		// allFriends->RegisterObject(player);
		// Since player is handled by allFriends list, it doesn't need to be deleted.

		broken = false;
		initialized = true;
	}

	void Terminate() {

		gameLoop->Terminate();
		player->Terminate();
		//allEnemies->Terminate();
		allFriends->Terminate();
		stageMap->Terminate();
		soundEffectsMap->Terminate();
		gamePanel->Terminate();
		spriteMap->Terminate();
		textureMap->Terminate();
		screen->Terminate();
		gameSystem->Terminate();
		config->Terminate();

		DELETENULL(gameLoop);
		DELETENULL(player);
		//DELETENULL(allEnemies);
		DELETENULL(allFriends);
		DELETENULL(stageMap);
		DELETENULL(soundEffectsMap);
		DELETENULL(gamePanel);
		DELETENULL(spriteMap);
		DELETENULL(textureMap);
		DELETENULL(screen);
		DELETENULL(gameSystem);
		DELETENULL(config);

		initialized = false;
		broken = false;		
	}
}
