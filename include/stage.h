#pragma once

#include <map>
#include <string>
#include "all_objects.h"

using namespace std;

class Stage : public AllObjects {
public:
	Stage(const char* stageId, const Sint16 x, const Sint16 y, const Uint16 w, const Uint16 h);
	~Stage();

	virtual void Init() throw();
	virtual void Terminate();

	void SetBackground(const char* spriteId) throw();

	void Render();

	typedef map< char, string > Dictionary;
	Dictionary dictionary;

	friend class StageMap;
protected:

	SDL_Rect rect;
	string stageId;	
	Sprite* background;
};
