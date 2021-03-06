#pragma once

#include "accelerable_object.h"
#include "door_object.h"
#include "number_power.h"
#include "sound_effect.h"
#include "player_shot.h"


class Player : public AccelerableObject {
	public:
		enum Command {
			nothing = 0,
			left,
			right,
			up,
			down,
			jump,
			fire
		};

		Player();
		~Player();

		void CommandSetOrReset(const Command& command, const bool set = true);

		// Test commands.
		void PrintStates();

		void Init() throw();
		void Terminate();

		void OnCollision(GameObject& other);
		bool CheckCollision(const GameObject& other);

		void HandleLogic();
		void Render();
		void Ressurrect();
		void Recover();

		void ShowPowerUps();

		void GetNumberPower(NumberPower& other);
		void LifeUp();
		void EnergyUp(const int energy);

		bool IsDying();

		friend class PlayerShot;
		friend class GamePanel;

		double lastGroundedX;
		double lastGroundedY;

	protected:
		SpriteFace* CreateSpriteFace();

		int power;
		int distance;
		int doubleJumps;
		int doubleJumpsNow;

		int maxPower;
		int maxDistance;
		int maxDoubleJumps;

		int shortDistance;

		int lifes;
		int lastEnergy;
		int nextLife;

	private:
		void IncreasePower(const int power);
		void IncreaseDistance(const int distance);
		void IncreaseJump(const int doubleJumps);


		void ActionDoor();
		void ActionJump();
		void ActionShot();

		double bAcceleration;
		double gAccelerationBase;

		bool fireIsOn;
		bool leftIsOn;
		bool rightIsOn;
		bool upIsOn;
		bool downIsOn;
		bool jumpIsOn;

		bool holdingJump;

		bool walking;
		bool untouchable;

		bool accelerationChanged;
		bool fireChanged;
		bool jumpChanged;

		bool blinker;

		sf::Clock clockUntouchable;
		sf::Clock clockBlink;
		sf::Clock clockUntouchableSound;

		int untouchableMiliSeconds;
		int blinkMiliSeconds;
		int untouchableSoundMiliSeconds;

		Projectile::Direction nextShotDirection;
		SoundEffect* sfxStep;
		SoundEffect* sfxStrongLaser;
		SoundEffect* sfxJump;
		SoundEffect* sfxDeath;
		SoundEffect* sfxPowerup;
		SoundEffect* sfxPortal;
		SoundEffect* sfxUntouchable;
		SoundEffect* sfxNewLife;
		SoundEffect* sfxFullEnergy;
		SoundEffect* sfxHurt;

		DoorObject* door;
};
