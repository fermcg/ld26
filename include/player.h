#pragma once

#include "accelerable_object.h"
#include "sound_effect.h"

class Player : public AccelerableObject {
	public:
		enum Command {
			nothing = 0,
			left,
			right,
			up,
			down,
			fire
		};

		Player();
		~Player();

		void CommandSetOrReset(const Command& command, const bool set = true);

		// Test commands.
		void PrintStates();

		void Init() throw();
		void Terminate();

		void OnCollision();

		void HandleLogic();

		friend class PlayerShot;
	protected:
		SpriteFace* CreateSpriteFace();

	private:
		double bAcceleration;

		bool fireIsOn;
		bool leftIsOn;
		bool rightIsOn;
		bool upIsOn;
		bool downIsOn;

		bool walking;

		bool accelerationChanged;
		bool fireChanged;
		SoundEffect* sfxStep;
		SoundEffect* sfxStrongLaser;
		SoundEffect* sfxJump;
		SoundEffect* sfxDeath;
};
