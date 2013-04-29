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

	boundingBox.x = 0;
	boundingBox.y = 0;
	boundingBox.w = 0;
	boundingBox.h = 0;

	energy = 1;
	damage = BigDamage;

	dead = false;
	solid = false;

	unbreakable = false;
	lethal = false;

	stage = NULL;
	isProjectile = false;
	isDoor = false;
	isPlayer = false;
}
GameObject::~GameObject() {

}

void GameObject::Init() throw() {

	spriteFace = CreateSpriteFace();

	Sprite* sprite = spriteFace->GetSequence()->GetSprite();
	w = sprite->rect.w;
	h = sprite->rect.h;

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

	this->BaseSystem::Terminate();
}

void GameObject::Render() {

	SDL_Rect rect;
	rect.x = (Sint16)(int)x;
	rect.y = (Sint16)(int)y;
	rect.w = w;
	rect.h = h;

	this->spriteFace->RenderCopy(&rect);
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

//	} else {
//
//		stage->LoopCheckForCollision(*this);
	}
}

void GameObject::OnCollision(GameObject& other) {

	if(energy < 0 || other.lethal) {

		if(!unbreakable) {

			dead = true;
		}
	}
}

void GameObject::HoldMeBack(AccelerableObject& other) {

	if(!solid) {

		return;
	}

	Sint16 thisX0, thisY0, thisXf, thisYf;
	Sint16 otherX0, otherY0, otherXf, otherYf;

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
			if(d > -4.0) {

				other.newY += d;
				zeroY = true;
			}
		}
	} else if(other.ySpeed < 0.0) {
		
		if(thisYf > otherY0) {

		//	other.newY++;
			double d = (double)(thisYf - otherY0);
			if(d < 4.0) {

				other.newY += d;
				zeroY = true;
			}
		}
	}

	//HoldMeBack(other);

	if(zeroX && !zeroY) {
	
		other.xSpeed = 0.0;
		other.xAcceleration = 0.0;
	}
	if(zeroY) {

		other.ySpeed = 0.0;
		other.yAcceleration = 0.0;
	}
	return;
	
}

bool GameObject::AmIGrounded(const AccelerableObject& other) {

	if(!solid) {

		return false;
	}

	Sint16 thisX0, thisY0, thisXf, thisYf;
	Sint16 otherX0, otherY0, otherXf, otherYf;

	this->GetCollisionBox(thisX0, thisY0, thisXf, thisYf);
	other.GetCollisionBox(otherX0, otherY0, otherXf, otherYf);

	if(thisY0 == otherYf && thisX0 < otherXf && thisXf > otherX0) {

		return true;
	}

	return false;
}
bool GameObject::CheckCollision(const GameObject& other) {

	Sint16 thisX0, thisY0, thisXf, thisYf;
	Sint16 otherX0, otherY0, otherXf, otherYf;

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

void GameObject::GetCollisionBox(Sint16& x0, Sint16& y0, Sint16& xf, Sint16& yf) const {

	x0 = (Sint16)x + boundingBox.x;
	xf = x0 + boundingBox.w;
	y0 = (Sint16)y + boundingBox.y;
	yf = y0 + boundingBox.h;	
}
