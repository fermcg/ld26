#include "stage.h"
#include "singletons.h"


Stage::Stage(const char* stageId, const Sint16 x, const Sint16 y, const Uint16 w, const Uint16 h) {

	this->stageId = stageId;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}
Stage::~Stage() {

}

void Stage::Init() throw() {
	
	this->AllObjects::Init();
}

void Stage::Terminate() {

	this->AllObjects::Terminate();
}

void Stage::SetBackground(const char* spriteId) throw() {

	background = Singleton::spriteMap->Get(spriteId);
}

void Stage::Render() {

	if(background != NULL) {

		background->RenderCopy(&rect, 0);
	}

	this->AllObjects::Render();
}
