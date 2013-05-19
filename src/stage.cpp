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
	
	viewWidth = 256;
	viewHeight = 144;

	stageMatrix = NULL;

}
Stage::~Stage() {

}

void Stage::Init() throw() {

	this->AllObjects::Init();

	stageMatrix = new StageRow[ySize];

	for (int j = 0; j < ySize; j++) {

		stageMatrix[j] = new StageCell::Ptr[xSize];
		for (int i = 0; i < xSize; i++) {

			stageMatrix[j][i] = NULL;
		}
	}
}

void Stage::Terminate() {

	this->AllObjects::Terminate();

	if (stageMatrix != NULL) {
		for (int j = 0; j < ySize; j++) {

			for (int i = 0; i < xSize; i++) {

				if (stageMatrix[j][i] != NULL) {

					delete stageMatrix[j][i];
				}
			}
			delete [] stageMatrix[j];
		}
		delete [] stageMatrix;
		stageMatrix = NULL;
	}
}

void Stage::RegisterObject(GameObject* gameObject) {

	if (gameObject->stationary) {

		int xPosition = gameObject->x / BrickObject::Width;
		int yPosition = gameObject->y / BrickObject::Height;

		if (xPosition >= 0 && xPosition < xSize && yPosition >= 0 && yPosition < ySize) {

			AddToMatrix(gameObject, xPosition, yPosition);
		}
	} else {
		nonStationary.push_back(gameObject);
	}
	AllObjects::RegisterObject(gameObject);
}

bool Stage::UnregisterObject(unsigned long gameObjectId) {
	AllObjects::ObjectMap::iterator it;

	it = objectMap.find(gameObjectId);
	if(it == objectMap.end()) {

		return false;
	}

	if (it->second->stationary) {

		int xPosition = it->second->x / BrickObject::Width;
		int yPosition = it->second->y / BrickObject::Height;

		if (xPosition >= 0 && xPosition < xSize && yPosition >= 0 && yPosition < ySize) {

			RemoveFromMatrix(it->second, xPosition, yPosition);
		}

	} else {
		StageCell::iterator itCell;
		
		for (itCell = nonStationary.begin(); itCell != nonStationary.end(); itCell++) {

			if ((*itCell)->gameObjectId == gameObjectId) {
				nonStationary.erase(itCell);
				break;
			}
		}
	}
	it->second->gameObjectId = 0;
	objectMap.erase(it);

	return true;
}

void Stage::GetMatrixRegion(const GameObject& object, int& xPosition, int& yPosition, int& xStop, int& yStop, const int xDiff, const int yDiff) {

	xPosition = object.x / BrickObject::Width - xDiff;
	yPosition = object.y / BrickObject::Height - yDiff;

	xStop = xPosition + 2 * xDiff + object.w / BrickObject::Width;
	yStop = yPosition + 2 * yDiff + object.h / BrickObject::Height;

	if (xPosition < 0) {

		xPosition = 0;
	}
	if (yPosition < 0) {

		yPosition = 0;
	}

	if (xStop > xSize) {

		xStop = xSize;
	}

	if (yStop > ySize) {

		yStop = ySize;
	}
}
bool Stage::LoopCheckForCollision(GameObject& gameObject) {

	bool result = false;

/*	int xPosition;
	int yPosition;
	int xStop;
	int yStop;

	GetMatrixRegion(gameObject, xPosition, yPosition, xStop, yStop);

	for(int j = yPosition;j < yStop; j++) {
		
		for(int i = xPosition; i < xStop; i++) {

			if (stageMatrix[j][i] != NULL) {

				StageCell::iterator it;
				for (it = stageMatrix[j][i]->begin(); it != stageMatrix[j][i]->end(); it++) {

					if ((*it)->CheckCollision(gameObject)) {
						(*it)->TakeThisHit(gameObject.damage);
						gameObject.TakeThisHit((*it)->damage);

						(*it)->OnCollision(gameObject);
						gameObject.OnCollision(*(*it));
						result = true;
					}
				}
			}
		}
	}*/
	StageCell::iterator it;
	for (it = nonStationary.begin(); it != nonStationary.end(); it++) {
		if ((*it)->CheckCollision(gameObject)) {
			(*it)->TakeThisHit(gameObject.damage);
			gameObject.TakeThisHit((*it)->damage);

			(*it)->OnCollision(gameObject);
			gameObject.OnCollision(*(*it));
			result = true;
		}
	}

	return result;
}

void Stage::HoldMeBack(AccelerableObject& other) {

	if(other.isProjectile) {

		return;
	}
	int xPosition;
	int yPosition;
	int xStop;
	int yStop;

	GetMatrixRegion(other, xPosition, yPosition, xStop, yStop);

	for(int j = yPosition;j < yStop; j++) {
		
		for(int i = xPosition; i < xStop; i++) {

			if (stageMatrix[j][i] != NULL) {

				StageCell::iterator it;
				for (it = stageMatrix[j][i]->begin(); it != stageMatrix[j][i]->end(); it++) {

					(*it)->HoldMeBack(other);
				}
			}
		}
	}
	StageCell::iterator it;
	for (it = nonStationary.begin(); it != nonStationary.end(); it++) {
		(*it)->HoldMeBack(other);
	}
}
bool Stage::AmIGrounded(const AccelerableObject& other) {

	int xPosition;
	int yPosition;
	int xStop;
	int yStop;

	GetMatrixRegion(other, xPosition, yPosition, xStop, yStop);
	groundObject = NULL;

	for(int j = yPosition;j < yStop; j++) {
		
		for(int i = xPosition; i < xStop; i++) {

			if (stageMatrix[j][i] != NULL) {

				StageCell::iterator it;
				for (it = stageMatrix[j][i]->begin(); it != stageMatrix[j][i]->end(); it++) {

					if ((*it)->AmIGrounded(other)) {
						groundObject = *it;
						return true;
					}
				}
			}
		}
	}
	StageCell::iterator it;
	for (it = nonStationary.begin(); it != nonStationary.end(); it++) {
		if ((*it)->AmIGrounded(other)) {
			groundObject = *it;
			return true;
		}
	}

	return false;
}

void Stage::TerminateObject(ObjectMap::iterator itDead) {

	StageCell::iterator it;
	for (it = nonStationary.begin(); it != nonStationary.end(); it++) {

		if ((*it)->gameObjectId == itDead->second->gameObjectId) {

			nonStationary.erase(it);
			break;
		}
	}
	AllObjects::TerminateObject(itDead);
}

void Stage::HandleLogic() {

	StageCell::iterator it;

	vector<int> cemetery;
	for (it = nonStationary.begin(); it != nonStationary.end(); it++) {

		if((*it)->dead) {

			cemetery.push_back((*it)->gameObjectId);
//			StageCell::iterator itDead = it;
//			if (it != nonStationary.begin()) {
//
//				it--;
//				nonStationary.erase(itDead);
//				it++;
//			} else {
//				nonStationary.erase(itDead);
//				it = nonStationary.begin();
//			}
		} else {

			(*it)->HandleLogic();
		}
	}

	vector<int>::const_iterator deathIt;
	for (deathIt = cemetery.begin(); deathIt != cemetery.end(); deathIt++) {

		AllObjects::ObjectMap::iterator it = objectMap.find(*deathIt);

		if (it != objectMap.end()) {

			TerminateObject(it);
		}
	}
}

void Stage::AddToMatrix(GameObject* gameObject, int xPosition, int yPosition) {

	if (stageMatrix[yPosition][xPosition] == NULL) {

		stageMatrix[yPosition][xPosition] = new StageCell();
	}

	stageMatrix[yPosition][xPosition]->push_back(gameObject);
}

void Stage::RemoveFromMatrix(GameObject* gameObject, int xPosition, int yPosition) {

	if (stageMatrix[yPosition][xPosition] != NULL) {

		StageCell::iterator it;
		
		for (it = stageMatrix[yPosition][xPosition]->begin(); it != stageMatrix[yPosition][xPosition]->end(); it++) {

			if ((*it)->gameObjectId == gameObject->gameObjectId) {
				stageMatrix[yPosition][xPosition]->erase(it);
				return;
			}
		}
	}
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

	Singleton::player->lastGroundedX = playerStartX;
	Singleton::player->lastGroundedY = playerStartY;
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

	/*int xPosition;
	int yPosition;
	int xStop;
	int yStop;

	GetMatrixRegion(*Singleton::player, xPosition, yPosition, xStop, yStop);
	groundObject = NULL;

	for(int j = yPosition;j < yStop; j++) {
		
		for(int i = xPosition; i < xStop; i++) {

			if (stageMatrix[j][i] != NULL) {

				StageCell::iterator it;
				for (it = stageMatrix[j][i]->begin(); it != stageMatrix[j][i]->end(); it++) {

					(*it)->Render();
				}
			}
		}
	}
	StageCell::iterator it;
	for (it = nonStationary.begin(); it != nonStationary.end(); it++) {

		(*it)->Render();
	}*/

	AllObjects::Render();
	
	if(!hideGamePanel) {
		
		Singleton::gamePanel->Render();
	}
}

GameObject* Stage::CreateObject(const string& objectClass,
								const string& objectFace,
								const double x, const double y,
								const bool respawn) {

	if (respawn) {

		Spawned *spawned = new Spawned(objectClass, objectFace);


		spawned->Init();
		RegisterObject(spawned);

		spawned->x = x;
		spawned->y = y;
		spawned->respawn = false;
		spawned->stage = this;

		spawnVector.push_back(spawned);
		return spawned;
	}

	GameObject* object = this->AllObjects::CreateObject(objectClass,
														objectFace, x, y,
														respawn);

	if(object != NULL) {

		object->stage = this;
	}

	return object;
}

void Stage::Spawn() {

	vector< Spawned* >::iterator it;

	for (it = spawnVector.begin(); it != spawnVector.end(); it++) {

		(*it)->StageInit();
	}
}

void Stage::Unspawn() {

	vector< Spawned* >::iterator it;

	for (it = spawnVector.begin(); it != spawnVector.end(); it++) {

		(*it)->StageEnd();
	}
}

Stage::Spawned::Spawned(const string& objectClass, const string& objectFace) : GameObject("Spawn", "Spawn") {

	this->object = NULL;
	this->objectClass = objectClass;
	this->objectFace = objectFace;

	unbreakable = true;
	damage = 0;
}

Stage::Spawned::~Spawned() {
}

void Stage::Spawned::Init() throw() {

	// bypass all the way to GameObject Inits on purpose
	BaseSystem::Init();
}

void Stage::Spawned::Terminate() {

	GameObject::Terminate();
}

void Stage::Spawned::StageInit() {

	if (!object) {

		object = stage->AllObjects::CreateObject(objectClass, objectFace, x, y, true);
		object->stage = stage;
	}
}

void Stage::Spawned::StageEnd() {

	if (object) {

		AllObjects::ObjectMap::iterator itDead = stage->objectMap.find(object->gameObjectId);

		if (itDead != stage->objectMap.end() ) {

			stage->TerminateObject(itDead);
		}

		object = NULL;
	}
}

void Stage::Spawned::Render() {
	// Nothing to render.
}

SpriteFace* Stage::Spawned::CreateSpriteFace() {

	return NULL;	
}

bool Stage::Spawned::CheckCollision(const GameObject& other) {

	return false; // never colide.
}