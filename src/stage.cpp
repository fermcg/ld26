#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "stage.h"
#include "brick_object.h"
#include "singletons.h"
#include "exceptions.h"
#include "macros.h"

using std::vector;
using std::string;

using std::cerr;

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

void Stage::PrepareFixedData() {
	
	AllObjects::ObjectMap::iterator it;
		
	cachedImage.create(xSize * BrickObject::Width, ySize * BrickObject::Height,
					   color);
	
	for(it = objectMap.begin(); it != objectMap.end(); it++) {
		
		if (it->second->preRender) {
			
			// render to cached image.
			it->second->RenderToImage(cachedImage);
		}
	}

	cachedTexture.loadFromImage(cachedImage);
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

void Stage::SetColor(const string& colorString) {

	vector<string> colorVector;
	
	boost::split(colorVector, colorString, boost::is_any_of(", "),
				 boost::token_compress_on);
	
	if (colorVector.size() < 3 || colorVector.size() > 4) {
		
		cerr << "Error setting stage color. invalid string ["
		<< colorString << "]" << endl;
		
		THROWINFO(Exception::BadConfigValue, colorString.c_str());
	}

	int r, g, b, a;
	
	try {
	
		r = boost::lexical_cast<int>(colorVector[0]);
		g = boost::lexical_cast<int>(colorVector[1]);
		b = boost::lexical_cast<int>(colorVector[2]);
		
		if (colorVector.size() == 4) {
			
			a = boost::lexical_cast<int>(colorVector[3]);
		} else {
			
			a = 0;
		}
	} catch(bad_cast&) {
		
		cerr << "Error setting stage color. non numeric ["
		<< colorString << "]" << endl;
		
		THROWINFO(Exception::BadConfigValue, colorString.c_str());
	}
	
	if (r < 0 || r > 255 ||
		g < 0 || g > 255 ||
		b < 0 || b > 255 ||
		a < 0 || a > 255) {
		
		cerr << "Error setting stage color. must be in [0-255] range ["
		<< colorString << "]" << endl;
		
		THROWINFO(Exception::BadConfigValue, colorString.c_str());
		
	}
	
	color.r = (sf::Uint8)r;
	color.g = (sf::Uint8)g;
	color.b = (sf::Uint8)b;
	color.a = (sf::Uint8)a;
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

	Singleton::screen->window->clear(color);
	sf::Sprite cachedSprite(cachedTexture);
	Singleton::screen->window->draw(cachedSprite);

	if(background != NULL) {

		//background->RenderCopy(&rect, 0);
		Singleton::screen->window->setView(Singleton::screen->noZoomView);
		background->RenderCopy();
		Singleton::screen->window->setView(Singleton::screen->view);
	}

	if(!hideGamePanel) {

		Singleton::gamePanel->Render();
	}

	if (noViewPort ) {
		
		Singleton::screen->window->setView(Singleton::screen->noZoomView);
	} else {

		double viewX, viewY;
		
		viewX = Singleton::player->x + Singleton::player->w / 2.0;
		viewY = Singleton::player->y + Singleton::player->h / 2.0;
		
		/*if (viewX < 0.0) {
			
			viewX = 0.0;
		}
		if (viewY < 0.1) {
			
			viewY = 0.1;
		}
		if (viewX > Singleton::screen->window->getSize().x) {
			
			viewX = Singleton::screen->window->getSize().x;
		}
		if (viewY > Singleton::screen->window->getSize().y) {
			
			viewY = Singleton::screen->window->getSize().y;
		}*/
		
		Singleton::screen->view.setCenter(viewX, viewY);
		Singleton::screen->view.setSize(viewWidth, viewHeight);
		
		Singleton::screen->HandleZoom();
		Singleton::screen->window->setView(Singleton::screen->view);
	}
	this->AllObjects::Render();
	
	if(!hideGamePanel) {
		
		Singleton::gamePanel->Render();
	}
}

GameObject* Stage::CreateObject(const string& objectClass,
								const string& objectFace) {

	GameObject* object = this->AllObjects::CreateObject(objectClass,
														objectFace);

	if(object != NULL) {

		object->stage = this;
	}

	return object;
}

