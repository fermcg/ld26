#pragma once

#include "base_system.h"
#include "stage.h"

class GameLoop : public BaseSystem {
	public:
		GameLoop();
		~GameLoop();

		void Init() throw();
		void Terminate();

		void Loop() throw();

		void GameOver();
		void ReloadStage();

		Stage* currentStage;
		friend class StageMap;

		long score;
	private:
		void LoopStart();
		void HandleEvents();
		void HandleLogic();
		void Render();
		void LoopEnd();

		bool keepWalking;
		bool gameOver;
		bool reloadStage;
		unsigned long loopCount;
};
