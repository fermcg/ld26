#pragma once

#include "accelerable_object.h"
#include "door_object.h"
#include "number_power.h"
#include "sound_effect.h"


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
		void Ressurrect();

		void GetNumberPower(NumberPower& other);

		friend class PlayerShot;
	protected:
		SpriteFace* CreateSpriteFace();

	private:
		void IncreaseHealth(const int energy);
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
		SoundEffect* sfxStep;
		SoundEffect* sfxStrongLaser;
		SoundEffect* sfxJump;
		SoundEffect* sfxDeath;
		SoundEffect* sfxPowerup;
		SoundEffect* sfxPortal;

		int distance;
		int doubleJumps;

		int maxEnergy;
		int maxDistance;
		int maxDoubleJumps;
		DoorObject* door;
};
