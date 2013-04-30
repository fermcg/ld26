#pragma once

#include <map>
#include <string>
#include "all_objects.h"

using namespace std;

class Stage : public AllObjects {
	public:
		Stage(const char* stageId, const int xPos, const int yPos, const int xSize, const int ySize);
		~Stage();

		virtual void Init() throw();
		virtual void Terminate();

		void SetBackground(const char* spriteId) throw();
		void SetHideGamePanel(const bool hideGamePanel);
		void SetPlayerStartPosition(const int x, const int y);
		void PositionPlayer();

		void Render();

		GameObject* CreateObject(const string& objectClass);

		typedef map< char, string > Dictionary;
		Dictionary dictionary;

		friend class StageMap;
	protected:

		SDL_Rect rect;
		int xPos;
		int yPos;
		int xSize;
		int ySize;

		int playerStartX;
		int playerStartY;

		bool hideGamePanel;

		string stageId;	
		Sprite* background;
};
