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
		void SetNoViewPort(const bool noViewPort);
		void SetPlayerStartPosition(const int x, const int y);
		void PositionPlayer();

		void Render();

		GameObject* CreateObject(const string& objectClass);

		typedef map< char, string > Dictionary;
		Dictionary dictionary;

		friend class StageMap;
	protected:

		sf::IntRect rect;
		int xPos;
		int yPos;
		int xSize;
		int ySize;

		int playerStartX;
		int playerStartY;

		bool hideGamePanel;
		bool noViewPort;
	
		double viewWidth;
		double viewHeight;

		string stageId;	
		Sprite* background;
};
