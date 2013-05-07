#pragma once

#include <string>
#include <SFML/Graphics.hpp>
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
		friend class GamePanel;

		bool unbreakable;
		bool lethal;
		bool solid;
		bool isProjectile;
		bool isDoor;
		bool isPlayer;
	protected:

		virtual SpriteFace* CreateSpriteFace() = 0;

		int w;
		int h;
		double x;
		double y;

		sf::IntRect boundingBox;
		SpriteFace* spriteFace;
		Stage* stage;
		unsigned long gameObjectId;

		int maxEnergy;

		int energy;
		int damage;

		bool dead;
	private:

		void GetCollisionBox(int& x0, int& y0, int& xf, int& yf) const;
};
