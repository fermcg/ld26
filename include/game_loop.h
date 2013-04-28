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

		Stage* currentStage;
		friend class StageMap;

	private:
		void LoopStart();
		void HandleEvents();
		void HandleLogic();
		void Render();
		void LoopEnd();

		bool keepWalking;
		unsigned long loopCount;
};
