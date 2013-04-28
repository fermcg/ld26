#include <iostream>
#include "player.h"
#include "player_shot.h"
#include "singletons.h"
#include "number_power.h"

using namespace std;

Player::Player() : AccelerableObject("Player", "Player") {

	bAcceleration = 0.005;
	gAcceleration = 0.005;

	// Accelerable vars

	xMinSpeed = 0.0;
	xMaxSpeed = 0.5;
	yMinSpeed = 0.0;
	yMaxSpeed = 0.5;

	xBreaking = 0.002;
	yBreaking = 0.002;

	fireIsOn = false;
	leftIsOn = false;
	rightIsOn = false;
	upIsOn = false;
	downIsOn = false;
	jumpIsOn = false;

	accelerationChanged = false;
	fireChanged = false;

	boundingBox.x = 1;
	boundingBox.y = 4;
	boundingBox.w = 4;
	boundingBox.h = 12;

	energy = 2000;
	damage = 2000;

	sfxStep = NULL;
	sfxStrongLaser = NULL;
	walking = false;

	power = 0;
	distance = 0;
	jumpHeight = 0;

	maxPower = 0;
	maxDistance = 0;
	maxJumpHeight = 0;
}

Player::~Player() {

}

void Player::Init() throw() {

	this->AccelerableObject::Init();

	sfxStep = Singleton::soundEffectsMap->Get("PLAYER+STEP");
	sfxStrongLaser = Singleton::soundEffectsMap->Get("STRONGLASER");
	sfxJump = Singleton::soundEffectsMap->Get("PLAYER+JUMP");
	sfxDeath = Singleton::soundEffectsMap->Get("PLAYER+DEATH");
	sfxPowerup = Singleton::soundEffectsMap->Get("POWERUP");

	SetNeverLeaveScreen(true);
	x = minX + (maxX - minX) / 2.0;
	y = maxY;
}

void Player::Terminate() {

	this->AccelerableObject::Terminate();
}

void Player::OnCollision(GameObject& other) {

	Singleton::energyBar->SetEnergy(energy);
	if(energy < 0) {

		dead = true;
		cout << "Game Over" << endl;
	}
}

void Player::HandleLogic() {

	this->AccelerableObject::HandleLogic();
	if(xAcceleration != 0.0 && !walking && grounded) {

		walking = true;
		sfxStep->Start(1);
	} else if (xAcceleration == 0.0 && walking || walking && !grounded) {

		walking = false;
		sfxStep->Stop(1);
	}
}

void Player::GetNumberPower(NumberPower& other) {

	switch(other.color) {

		case NumberPower::red:
			IncreasePower(other.number);
			break;
		case NumberPower::green:
			IncreaseDistance(other.number);
			break;
		case NumberPower::blue:
			IncreaseJump(other.number);
			break;
	}
	sfxPowerup->Play(4);
}

void Player::IncreasePower(const int power) {

	this->power += power;
	if(this->power > maxPower) {

		this->power = maxPower;
	}
}

void Player::IncreaseDistance(const int distance) {

	this->distance += distance;
	if(this->distance > maxDistance) {

		this->distance = maxDistance;
	}
}

void Player::IncreaseJump(const int jumpHeight) {

	this->jumpHeight += jumpHeight;
	if(this->jumpHeight > maxJumpHeight) {

		this->jumpHeight = maxJumpHeight;
	}
}

SpriteFace* Player::CreateSpriteFace() {

	SpriteFace* face = new SpriteFace("Player Face");

	face->RegisterFace(SpriteFace::front, "PLAYER+FRONT");
	face->RegisterFace(SpriteFace::left, "PLAYER+LEFT");
	face->RegisterFace(SpriteFace::right, "PLAYER+RIGHT");
	face->RegisterFace(SpriteFace::jumping_front, "PLAYER+JUMP+FRONT");
	face->RegisterFace(SpriteFace::jumping_left, "PLAYER+JUMP+LEFT");
	face->RegisterFace(SpriteFace::jumping_right, "PLAYER+JUMP+RIGHT");

	return face;
}

void Player::CommandSetOrReset(const Player::Command& command, const bool set) {

	bool changed = false;

	switch(command) {

		case nothing:
			break;
		case left:
			if(leftIsOn != set) {

				leftIsOn = set;
				changed = true;
				accelerationChanged = true;
			}
			break;
		case right:
			if(rightIsOn != set) {

				rightIsOn = set;
				changed = true;
				accelerationChanged = true;
			}
			break;
		case up:
			if(upIsOn != set) {

				upIsOn = set;
				changed = true;
			}
			break;
		case down:
			if(downIsOn != set) {

			}
			break;
		case jump:
			if(jumpIsOn != set) {

				jumpIsOn = set;
				changed = true;
			}
			break;
		case fire:
			if(fireIsOn != set) {

				fireIsOn = set;
				changed = true;
				fireChanged = true;
			}
			break;
	}

	if(changed) {

		if(jumpIsOn && grounded) {

			ySpeed = -yMaxSpeed;
			sfxJump->Play(3);
		}
		if(accelerationChanged) {

			xAcceleration = (leftIsOn ? -bAcceleration : 0.0) + (rightIsOn ? bAcceleration : 0.0);
			yAcceleration = (upIsOn ? -bAcceleration : 0.0) + (downIsOn ? bAcceleration : 0.0);
			accelerationChanged = false;
		}
		if(fireChanged) {
			fireChanged = false;

			if(!fireIsOn) {
				sfxStrongLaser->Play(2);			
				/*	PlayerShot *shot = new PlayerShot(*this);
					shot->Init();
					Singleton::allFriends->RegisterObject(shot);*/
			}
		}
	}

}

void Player::PrintStates() {

	if(accelerationChanged || fireChanged) {

		cout << "\r button states: ";

		cout << " l" << (leftIsOn ? "<" : ".");
		cout << " r" << (rightIsOn ? ">" : ".");
		cout << " u" << (upIsOn ? "^" : ".");
		cout << " d" << (downIsOn ? "v" : ".");
		cout << " f" << (fireIsOn ? "+" : ".");

		cout << " cmd states: ";
		if(yAcceleration == 0.0) {
			cout << "o";
		} else if(yAcceleration < 0.0) {
			cout << "^";
		} else {
			cout << "v";
		}

		if(xAcceleration == 0.0) {
			cout << "o";
		} else if(xAcceleration < 0.0) {
			cout << "<";
		} else {
			cout << ">";
		}

		if(fireIsOn) {
			cout << "+";
		} else {
			cout << "o";
		}

		cout.flush();

		accelerationChanged = false;
		fireChanged = false;
	}

}
