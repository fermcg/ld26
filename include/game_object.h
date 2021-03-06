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
		virtual void RenderToImage(sf::Image& destinyImage) throw();

		virtual void HandleLogic();
		virtual void OnCollision(GameObject& other);

		void HoldMeBack(AccelerableObject& other);
		bool AmIGrounded(const AccelerableObject& other);
		virtual bool CheckCollision(const GameObject& other);
		virtual void TakeThisHit(const int damage);

		virtual bool Merge(GameObject* other);
	
		void ChangeFace(const string& objectFace);

		static const int BigDamage;	
		friend class AllObjects;
		friend class StageMap;
		friend class Stage;
		friend class GamePanel;

		bool unbreakable;
		bool lethal;
		bool solid;
		bool verticalSolid;
		bool mirrored;
		bool smartBricks;
		bool preRender;
		bool respawn;
		bool stationary;
		bool isProjectile;
		bool isDoor;
		bool isPlayer;

		bool isEnemy;
		bool isBouncer;
		bool isDog;
		bool isAlien;

		bool isPickable;
		bool isHurting;

		double xAdjust;
		double yAdjust;
		double xAdjustAcceleration;
		double yAdjustAcceleration;

	protected:

		virtual SpriteFace* CreateSpriteFace() = 0;

		SpriteFace* CreateSmartBricksFace(const char* prefixId);
		SpriteFace* CreateWalkingCharFace(const char* prefixId);
		int w;
		int h;
		double x;
		double y;
	
		long scoreValue;

		sf::IntRect boundingBox;
		SpriteFace* spriteFace;
		Stage* stage;
		unsigned long gameObjectId;

		int maxEnergy;

		int energy;
		int damage;

		bool dead;
		string objectFace;
	private:

		void GetCollisionBox(int& x0, int& y0, int& xf, int& yf) const;
};
