#include <iostream>

#include "game_object.h"
#include "singletons.h"
#include "macros.h"
#include "exceptions.h"

using namespace std;

// constants
const int GameObject::BigDamage = 100000;

GameObject::GameObject(const char* name, const char* objectId, const char* spriteId) : BaseSystem(name) {
	
	this->objectId = objectId;
	this->spriteId = spriteId;
	this->sprite = NULL;
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
	
	enemy = true; // Since there will be more enemies than allies - enemy is default
	dead = false;
}
GameObject::~GameObject() {
	
}

void GameObject::Init() throw() {
	
	sprite = Singleton::spriteMap->Get(spriteId.c_str());
	
	w = sprite->rect.w;
	h = sprite->rect.h;
	
	this->BaseSystem::Init();
}

void GameObject::Terminate() {
	
	if(gameObjectId != 0) {
		
		bool unregistered = false;
		if(enemy) {
			
			unregistered = Singleton::allEnemies->UnregisterObject(gameObjectId);
		} else {
			
			unregistered = Singleton::allFriends->UnregisterObject(gameObjectId);
		}
		if(!unregistered) {
			
			string fullName = GetFullName();
			cerr << "Object Id not found [" << gameObjectId << "] -> can't unregister ["
			 	<< fullName << "] from " << (enemy ? "allEnemies" : "allFriends") << " list";
			THROWINFO(Exception::ObjectNotFound, fullName.c_str());
		}
	}
	this->BaseSystem::Terminate();
}

void GameObject::Render() {
	
	SDL_Rect rect;
	rect.x = (Sint16)(int)x;
	rect.y = (Sint16)(int)y;
	rect.w = w;
	rect.h = h;
	
	this->sprite->RenderCopy(&rect);
}

void GameObject::HandleLogic() {
	
	if(enemy) {
		
		Singleton::allFriends->LoopCheckForCollision(*this);
	}
}

void GameObject::OnCollision() {
	
	if(energy < 0) {
		
		dead = true;
	}
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
	
	if(energy >= 0) {
		
		energy -= damage;
	}
}

void GameObject::GetCollisionBox(Sint16& x0, Sint16& y0, Sint16& xf, Sint16& yf) const {
	
	x0 = (Sint16)x + boundingBox.x;
	xf = x0 + boundingBox.w;
	y0 = (Sint16)y + boundingBox.y;
	yf = y0 + boundingBox.h;	
}
