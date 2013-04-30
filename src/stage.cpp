#include "stage.h"
#include "brick_object.h"
#include "singletons.h"


Stage::Stage(const char* stageId, const int xPos, const int yPos, const int xSize, const int ySize) {

	this->stageId = stageId;

	this->xPos = xPos;
	this->yPos = yPos;
	this->xSize = xSize;
	this->ySize = ySize;

	rect.x = BrickObject::Width * xPos;
	rect.y = BrickObject::Height * yPos;
	rect.w = BrickObject::Width * xSize;
	rect.h = BrickObject::Height * ySize;

	playerStartX = 0;
	playerStartY = 0;
	background = NULL;
	hideGamePanel = false;
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

void Stage::SetHideGamePanel(const bool hideGamePanel) {

	this->hideGamePanel = hideGamePanel;
}

void Stage::SetPlayerStartPosition(const int x, const int y) {

	playerStartX = (xPos + x) * BrickObject::Width;
	playerStartY = (yPos + y) * BrickObject::Height;
}

void Stage::PositionPlayer() {

	Singleton::player->x = playerStartX;
	Singleton::player->y = playerStartY;
}

void Stage::Render() {

	if(background != NULL) {

		//background->RenderCopy(&rect, 0);
		background->RenderCopy();
	}

	if(!hideGamePanel) {

		Singleton::gamePanel->Render();
	}

	this->AllObjects::Render();
}

GameObject* Stage::CreateObject(const string& objectClass) {

	GameObject* object = this->AllObjects::CreateObject(objectClass);

	if(object != NULL) {

		object->stage = this;
	}

	return object;
}

