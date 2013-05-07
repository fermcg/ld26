#include "stage.h"
#include "brick_object.h"
#include "singletons.h"


Stage::Stage(const char* stageId, const int xPos, const int yPos, const int xSize, const int ySize) {

	this->stageId = stageId;

	this->xPos = xPos;
	this->yPos = yPos;
	this->xSize = xSize;
	this->ySize = ySize;

	rect.left = BrickObject::Width * xPos;
	rect.top = BrickObject::Height * yPos;
	rect.width = BrickObject::Width * xSize;
	rect.height = BrickObject::Height * ySize;

	playerStartX = 0;
	playerStartY = 0;
	background = NULL;
	hideGamePanel = false;
	noViewPort = false;
	
	viewWidth = 258;
	viewHeight = 192;
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

void Stage::SetNoViewPort(const bool noViewPort) {
	
	this->noViewPort = noViewPort;
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
		Singleton::screen->window->setView(Singleton::gamePanel->view);
		background->RenderCopy();
		Singleton::screen->window->setView(*Singleton::screen->view);
	}

	if(!hideGamePanel) {

		Singleton::gamePanel->Render();
	}

	if (noViewPort ) {
		
		Singleton::screen->window->setView(Singleton::gamePanel->view);
	} else {
		double viewX, viewY;
		
		viewX = Singleton::player->x + Singleton::player->w / 2.0;
		viewY = Singleton::player->y + Singleton::player->h / 2.0;
		
		if (viewX < 0.0) {
			
			viewX = 0.0;
		}
		if (viewY < 0.0) {
			
			viewY = 0.0;
		}
		if (viewX > Singleton::screen->window->getSize().x) {
			
			viewX = Singleton::screen->window->getSize().x;
		}
		if (viewY > Singleton::screen->window->getSize().y) {
			
			viewY = Singleton::screen->window->getSize().y;
		}
		
		Singleton::screen->view->setCenter(viewX, viewY);
		Singleton::screen->view->setSize(viewWidth, viewHeight);
		
		Singleton::screen->window->setView(*Singleton::screen->view);
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

