#pragma once

#include <string>
#include <SDL.h>
#include "base_system.h"
#include "sprite_face.h"

using namespace std;

class GameObject : public BaseSystem {
public:
	
	GameObject(const char* name, const char* objectId);
	~GameObject();
	
	virtual void Init() throw();
	virtual void Terminate();

	void Render();
	virtual void HandleLogic();
	virtual void OnCollision();
	
	bool CheckCollision(const GameObject& other);
	void TakeThisHit(const int damage);

	static const int BigDamage;	
	friend class AllObjects;
protected:
	
	virtual SpriteFace* CreateSpriteFace() = 0;
	
	Uint16 w;
	Uint16 h;
	double x;
	double y;
	
	SDL_Rect boundingBox;
	SpriteFace* spriteFace;
	unsigned long gameObjectId;
	
	int energy;
	int damage;
	bool enemy;
	
	bool dead;
private:
	
	void GetCollisionBox(Sint16& x0, Sint16& y0, Sint16& xf, Sint16& yf) const;
};
