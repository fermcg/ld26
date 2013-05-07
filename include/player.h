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

		void HandleLogic();
		void Render();
		void Ressurrect();

		void ShowPowerUps();

		void GetNumberPower(NumberPower& other);

		friend class PlayerShot;
		friend class GamePanel;
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

	private:
		void IncreasePower(const int power);
		void IncreaseDistance(const int distance);
		void IncreaseJump(const int doubleJumps);


		void ActionDoor();
		void ActionJump();
		void ActionShot();

		double bAcceleration;

		bool fireIsOn;
		bool leftIsOn;
		bool rightIsOn;
		bool upIsOn;
		bool downIsOn;
		bool jumpIsOn;

		bool walking;

		bool accelerationChanged;
		bool fireChanged;
		Projectile::Direction nextShotDirection;
		SoundEffect* sfxStep;
		SoundEffect* sfxStrongLaser;
		SoundEffect* sfxJump;
		SoundEffect* sfxDeath;
		SoundEffect* sfxPowerup;
		SoundEffect* sfxPortal;

		DoorObject* door;
};
