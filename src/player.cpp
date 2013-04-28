#include <iostream>
#include "player.h"
#include "player_shot.h"
#include "singletons.h"

using namespace std;

Player::Player() : AccelerableObject("Player", "Player") {

	bAcceleration = 0.0005;

	// Accelerable vars

	xMinSpeed = 0.0;
	xMaxSpeed = 0.15;
	yMinSpeed = 0.0;
	yMaxSpeed = 0.15;

	xBreaking = 0.0002;
	yBreaking = 0.0002;

	fireIsOn = false;
	leftIsOn = false;
	rightIsOn = false;
	upIsOn = false;
	downIsOn = false;

	accelerationChanged = false;
	fireChanged = false;

	boundingBox.x = 8;
	boundingBox.y = 0;
	boundingBox.w = 16;
	boundingBox.h = 32;

	enemy = false;

	energy = 2000;
	damage = 2000;

	sfxStep = NULL;
	sfxStrongLaser = NULL;
	walking = false;
}

Player::~Player() {

}

void Player::Init() throw() {

	this->AccelerableObject::Init();

	sfxStep = Singleton::soundEffectsMap->Get("PLAYER+STEP");
	sfxStrongLaser = Singleton::soundEffectsMap->Get("STRONGLASER");

	SetNeverLeaveScreen(true);
	x = minX + (maxX - minX) / 2.0;
	y = maxY;
}

void Player::Terminate() {

	this->AccelerableObject::Terminate();
}

void Player::OnCollision() {

	if(energy < 0) {

		dead = true;
		cout << "Game Over" << endl;
	}
}

void Player::HandleLogic() {

	this->AccelerableObject::HandleLogic();
	if(xAcceleration != 0.0 && !walking) {

		walking = true;
		sfxStep->Start(1);
	} else if (xAcceleration == 0.0 && walking) {

		walking = false;
		sfxStep->Stop(1);
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
				accelerationChanged = true;
			}
			break;
		case down:
			if(downIsOn != set) {

				downIsOn = set;
				changed = true;
				accelerationChanged = true;
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
