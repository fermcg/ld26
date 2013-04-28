#pragma once

#include <string>
#include <SDL.h>
#include "base_system.h"
#include "sprite_face.h"

using namespace std;

class Stage;
class AccelerableObject;
class GameObject : public BaseSystem {
	public:

		GameObject(const char* name, const char* objectId);
		~GameObject();

		virtual void Init() throw();
		virtual void Terminate();

		virtual void Render();
		virtual void HandleLogic();
		virtual void OnCollision(GameObject& other);

		void HoldMeBack(AccelerableObject& other);
		bool AmIGrounded(const AccelerableObject& other);
		bool CheckCollision(const GameObject& other);
		void TakeThisHit(const int damage);

		virtual bool Merge(GameObject* other);

		static const int BigDamage;	
		friend class AllObjects;
		friend class StageMap;
		friend class Stage;
	protected:

		virtual SpriteFace* CreateSpriteFace() = 0;

		Uint16 w;
		Uint16 h;
		double x;
		double y;

		SDL_Rect boundingBox;
		SpriteFace* spriteFace;
		Stage* stage;
		unsigned long gameObjectId;

		int energy;
		int damage;

		bool dead;
		bool unbreakable;
		bool lethal;
		bool solid;
	private:

		void GetCollisionBox(Sint16& x0, Sint16& y0, Sint16& xf, Sint16& yf) const;
};
