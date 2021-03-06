#include <iostream>

#include "game_object.h"
#include "singletons.h"
#include "macros.h"
#include "exceptions.h"

using namespace std;

// constants
const int GameObject::BigDamage = 100000;

GameObject::GameObject(const char* name, const char* objectId) : BaseSystem(name) {

	this->objectId = objectId;
	this->spriteFace = NULL;
	this->x = 0.0;
	this->y = 0.0;
	this->w = 0;
	this->h = 0;
	gameObjectId = 0;

	boundingBox.left = 0;
	boundingBox.top = 0;
	boundingBox.width = 0;
	boundingBox.height = 0;

	xAdjust = 1.0;
	yAdjust = 1.0;
	xAdjustAcceleration = 1.0;
	yAdjustAcceleration = 1.0;


	scoreValue = 0;
	
	maxEnergy = 1;
	energy = 1;
	damage = BigDamage;

	dead = false;
	solid = false;
	verticalSolid = false;

	unbreakable = false;
	lethal = false;
	preRender = false;
	respawn = false;
	stationary = false;

	stage = NULL;
	isProjectile = false;
	isDoor = false;
	isPlayer = false;

	isEnemy = false;
	isBouncer = false;
	isDog = false;
	isAlien = false;

	isPickable = false;
	isHurting = false;
	mirrored = false;
	smartBricks = false;
}
GameObject::~GameObject() {

}

void GameObject::Init() throw() {

	if (objectFace.empty()) {
		
		spriteFace = CreateSpriteFace();
	} else {
		
		spriteFace = new SpriteFace("Game Object Face");
		
		spriteFace->RegisterFace(SpriteFace::front, objectFace.c_str());

	}

	Sprite* sprite = spriteFace->GetSequence()->GetSprite();
	w = sprite->rect.width;
	h = sprite->rect.height;

	//Singleton::gameLoop->score += scoreValue;
	this->BaseSystem::Init();
}

void GameObject::Terminate() {

	if(gameObjectId != 0) {

		bool unregistered = false;
		if(stage != NULL) {

			unregistered = stage->UnregisterObject(gameObjectId);
		} else {

			unregistered = Singleton::allFriends->UnregisterObject(gameObjectId);
		}
		if(!unregistered) {

			string fullName = GetFullName();
			cerr << "Object Id not found [" << gameObjectId << "] -> can't unregister ["
				<< fullName << "] from " << (stage != NULL ? "stage object" : "allFriends") << " list";
			THROWINFO(Exception::ObjectNotFound, fullName.c_str());
		}
	}

	if(spriteFace != NULL) {
		spriteFace->Terminate();
		delete spriteFace;
		spriteFace = NULL;
	}

	//Singleton::gameLoop->score += scoreValue;
	this->BaseSystem::Terminate();
}

void GameObject::Render() {

	sf::IntRect rect;
	rect.left = (int)x;
	rect.top = (int)y;
	rect.width = w;
	rect.height = h;

	this->spriteFace->RenderCopy(&rect);
}

void GameObject::RenderToImage(sf::Image& destinyImage) throw() {
	
	if (spriteFace == NULL) {
		
		return;
	}
	this->spriteFace->RenderToImage(destinyImage, (int)x, (int)y);
}

void GameObject::HandleLogic() {

	if(stage != NULL) {

		Singleton::allFriends->LoopCheckForCollision(*this);
		if(Singleton::player->CheckCollision(*this)) {

			Singleton::player->TakeThisHit(this->damage);
			this->TakeThisHit(Singleton::player->damage);

			Singleton::player->OnCollision(*this);
			this->OnCollision(*Singleton::player);
		}

	} else {

		if (isProjectile) {
			Singleton::gameLoop->currentStage->LoopCheckForCollision(*this);
		}
	}
}

void GameObject::OnCollision(GameObject& other) {

	if(energy < 0 || other.lethal) {

		if(!unbreakable) {

			dead = true;

			if (!isPlayer) {

				Singleton::gameLoop->score += scoreValue;
			}
		}
	}
}

void GameObject::HoldMeBack(AccelerableObject& other) {

	if(!solid && !verticalSolid && !other.isBouncer) {

		return;
	}

	int thisX0, thisY0, thisXf, thisYf;
	int otherX0, otherY0, otherXf, otherYf;

	this->GetCollisionBox(thisX0, thisY0, thisXf, thisYf);
	other.GetNewCollisionBox(otherX0, otherY0, otherXf, otherYf);

	if(thisYf <= otherY0) {

		return;
	}
	if(thisY0 >= otherYf) {

		return;
	}
	if(thisXf <= otherX0) {

		return;
	}
	if(thisX0 >= otherXf) {

		return;
	}

	bool zeroX = false;
	bool zeroY = false;
	if(other.xSpeed > 0.0) {
	   
		if(thisX0 < otherXf) {

		//	other.newX--;
			double d = (double)(thisX0 - otherXf);
			if(d > -4.0) {

				other.newX += d;
				zeroX = true;
			}
		}
	} else if(other.xSpeed < 0.0) {

		if(thisXf > otherX0) {

		//	other.newX++;
			double d = (double)(thisXf - otherX0);
			if(d < 4.0) {

				other.newX += d;
				zeroX = true;
			}
		}
	}
	if(other.ySpeed > 0.0) {

		if(thisY0 < otherYf) {

		//	other.newY--;
			double d = (double)(thisY0 - otherYf);
			if(d > -4.0 && (!verticalSolid || other.isBouncer)) {

				other.newY += d;
				zeroY = true;
			}
		}
	} else if(other.ySpeed < 0.0) {
		
		if(thisYf > otherY0) {

		//	other.newY++;
			double d = (double)(thisYf - otherY0);
			if(d < 4.0 && (!verticalSolid || other.isBouncer)) {

				other.newY += d;
				zeroY = true;
			}
		}
	}

	//HoldMeBack(other);

	if (other.isPlayer) {
		
		if(zeroX && !zeroY) {
	
			other.xSpeed = 0.0;
//			other.xAcceleration = 0.0;
		}
		if(zeroY && !verticalSolid) {

			other.ySpeed = 0.0;
			other.yAcceleration = 0.0;
		}
	}
	
	if (other.isBouncer) {
		
		if (zeroX) {
			
			other.xSpeed = 0.0;
			other.xAcceleration = -other.xAcceleration;
		}
		if (zeroY) {
			
			other.ySpeed = 0.0;
			other.yAcceleration = -other.yAcceleration;
		}
	}
	
	return;
	
}

bool GameObject::AmIGrounded(const AccelerableObject& other) {

	if(!solid) {

		return false;
	}

	int thisX0, thisY0, thisXf, thisYf;
	int otherX0, otherY0, otherXf, otherYf;

	this->GetCollisionBox(thisX0, thisY0, thisXf, thisYf);
	other.GetCollisionBox(otherX0, otherY0, otherXf, otherYf);

	if(thisY0 == otherYf && thisX0 < otherXf && thisXf > otherX0) {

		return true;
	}

	return false;
}
bool GameObject::CheckCollision(const GameObject& other) {

	int thisX0, thisY0, thisXf, thisYf;
	int otherX0, otherY0, otherXf, otherYf;

	this->GetCollisionBox(thisX0, thisY0, thisXf, thisYf);
	other.GetCollisionBox(otherX0, otherY0, otherXf, otherYf);

	if(thisYf <= otherY0) {

		return false;
	}
	if(thisY0 >= otherYf) {

		return false;
	}
	if(thisXf <= otherX0) {

		return false;
	}
	if(thisX0 >= otherXf) {

		return false;
	}

	return true;
}

void GameObject::TakeThisHit(const int damage) {

	if(!unbreakable && energy >= 0) {

		energy -= damage;
	}
}

bool GameObject::Merge(GameObject* other) {

	return false; // Not implemented by default.
}

void GameObject::ChangeFace(const string &objectFace) {
	
	this->objectFace = objectFace;
}

SpriteFace* GameObject::CreateSmartBricksFace(const char* prefixId) {

	string brickId = prefixId;

	SpriteFace* face = new SpriteFace((brickId + " Face").c_str());


	brickId += "+";
	face->RegisterFace(SpriteFace::top_left    , (brickId + "TLEFT").c_str());
	face->RegisterFace(SpriteFace::up          , (brickId + "UP").c_str());
	face->RegisterFace(SpriteFace::top_right   , (brickId + "TRIGHT").c_str());
	face->RegisterFace(SpriteFace::full_up     , (brickId + "FUP").c_str());
	face->RegisterFace(SpriteFace::left        , (brickId + "LEFT").c_str());
	face->RegisterFace(SpriteFace::front       , (brickId + "FRONT").c_str());
	face->RegisterFace(SpriteFace::right       , (brickId + "RIGHT").c_str());
	face->RegisterFace(SpriteFace::vertical    , (brickId + "VERTICAL").c_str());
	face->RegisterFace(SpriteFace::bottom_left , (brickId + "BLEFT").c_str());
	face->RegisterFace(SpriteFace::down        , (brickId + "DOWN").c_str());
	face->RegisterFace(SpriteFace::bottom_right, (brickId + "BRIGHT").c_str());
	face->RegisterFace(SpriteFace::full_down   , (brickId + "FDOWN").c_str());
	face->RegisterFace(SpriteFace::full_left   , (brickId + "FLEFT").c_str());
	face->RegisterFace(SpriteFace::horizontal  , (brickId + "HORIZONTAL").c_str());
	face->RegisterFace(SpriteFace::full_right  , (brickId + "FRIGHT").c_str());
	face->RegisterFace(SpriteFace::full_front  , (brickId + "FFRONT").c_str());

	return face;
}

SpriteFace* GameObject::CreateWalkingCharFace(const char* prefixId) {
	string characterId = prefixId;

	SpriteFace* face = new SpriteFace((characterId + " Face").c_str());

	characterId += "+";
	face->RegisterFace(SpriteFace::right    , (characterId + "RIGHT").c_str());
	face->RegisterFace(SpriteFace::left     , (characterId + "LEFT").c_str());
	face->RegisterFace(SpriteFace::front    , (characterId + "FRONT").c_str());
	face->RegisterFace(SpriteFace::alt_front, (characterId + "ALT+FRONT").c_str());
	face->RegisterFace(SpriteFace::alt_right, (characterId + "ALT+RIGHT").c_str());
	face->RegisterFace(SpriteFace::alt_left , (characterId + "ALT+LEFT").c_str());
	face->RegisterFace(SpriteFace::dying    , (characterId + "DEATH").c_str());

	return face;

}

void GameObject::GetCollisionBox(int& x0, int& y0, int& xf, int& yf) const {

	x0 = (int)x + boundingBox.left;
	xf = x0 + boundingBox.width;
	y0 = (int)y + boundingBox.top;
	yf = y0 + boundingBox.height;	
}
