#include <iostream>
#include "player.h"
#include "player_shot.h"
#include "singletons.h"
#include "number_power.h"
#include "door_object.h"

using namespace std;

Player::Player() : AccelerableObject("Player", "Player") {

	bAcceleration = 0.04;
	gAcceleration = 0.03;

	// Accelerable vars

	xMinSpeed = 0.0;
	xMaxSpeed = 1.3;
	yMinSpeed = 0.0;
	yMaxSpeed = 1.6;

	xBreaking = 0.05;
	yBreaking = 0.05;

	fireIsOn = false;
	leftIsOn = false;
	rightIsOn = false;
	upIsOn = false;
	downIsOn = false;
	jumpIsOn = false;

	accelerationChanged = false;
	fireChanged = false;

	boundingBox.left = 1;
	boundingBox.top = 4;
	boundingBox.width = 5;
	boundingBox.height = 12;

	damage = 2000;

	sfxStep = NULL;
	sfxStrongLaser = NULL;
	sfxJump = NULL;
	sfxDeath = NULL;
	sfxPowerup = NULL;
	sfxPortal = NULL;
	door = NULL;
	walking = false;
	isPlayer = true;


	maxEnergy = 5000;
	maxPower = 9;
	maxDistance = 10;
	maxDoubleJumps = 10;

	energy = maxEnergy;
	power = 0;
	distance = 0;
	doubleJumps = 0;
	doubleJumpsNow = 0;

	shortDistance = 4;
	nextShotDirection = Projectile::down;
}

Player::~Player() {

}

void Player::Ressurrect() {

	energy = maxEnergy;
	dead = false;
	distance = 0;
	doubleJumps = 0;
}

void Player::Init() throw() {

	this->AccelerableObject::Init();

	sfxStep = Singleton::soundEffectsMap->Get("PLAYER+STEP");
	sfxStrongLaser = Singleton::soundEffectsMap->Get("STRONGLASER");
	sfxJump = Singleton::soundEffectsMap->Get("PLAYER+JUMP");
	sfxDeath = Singleton::soundEffectsMap->Get("PLAYER+DEATH");
	sfxPowerup = Singleton::soundEffectsMap->Get("POWERUP");
	sfxPortal = Singleton::soundEffectsMap->Get("PORTAL");

	SetNeverLeaveScreen(true);
	x = minX + (maxX - minX) / 2.0;
	y = maxY;
}

void Player::Terminate() {

	this->AccelerableObject::Terminate();
}

void Player::OnCollision(GameObject& other) {

	if(energy < 0) {

		dead = true;
		sfxDeath->Play();
		cout << "Game Over" << endl;

		Singleton::gameLoop->GameOver();
		return;
		Stage* nextStage = Singleton::stageMap->Get("MENU");
		if(nextStage != NULL) {

			Singleton::gameLoop->currentStage = nextStage;
			nextStage->PositionPlayer();
			Ressurrect();
		} else {

			cerr << "Error" << endl;
		}
		return;
	}
	if(other.isDoor) {

		door = reinterpret_cast< DoorObject* >(&other);
	}
}

void Player::HandleLogic() {

	door = NULL;
	
	if(xAcceleration > 0.0) {

		spriteFace->ChangeFace(SpriteFace::right);
	} else if(xAcceleration < 0.0) {

		spriteFace->ChangeFace(SpriteFace::left);
	} else if(downIsOn) {

		spriteFace->ChangeFace(SpriteFace::front);
	} else if(xAcceleration == 0.0) {

		spriteFace->ChangeFace(SpriteFace::front);
	}

	if (leftIsOn && !rightIsOn) {
		nextShotDirection = Projectile::left;
	} else if (rightIsOn && !leftIsOn) {
		nextShotDirection = Projectile::right;
	} else if (upIsOn && !downIsOn) {
		nextShotDirection = Projectile::up;
	} else if (downIsOn && !upIsOn) {
		nextShotDirection = Projectile::down;
	}

	this->AccelerableObject::HandleLogic();
	if(xAcceleration != 0.0 && !walking && grounded) {

		walking = true;
		sfxStep->Start();
	} else if (walking && (xAcceleration == 0.0 || !grounded)) {

		walking = false;
		sfxStep->Stop();
	}
	if (grounded) {

		doubleJumpsNow = 0;
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
	sfxPowerup->Play();
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

void Player::IncreaseJump(const int doubleJumps) {

	this->doubleJumps += doubleJumps;
	if(this->doubleJumps >= maxDoubleJumps) {

		this->doubleJumps = maxDoubleJumps - 1;
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
				
				downIsOn = set;
				changed = true;
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

		if(upIsOn) {

			ActionDoor();
		}
		if(jumpIsOn) {

			ActionJump();
		}
		if(accelerationChanged) {

			xAcceleration = (leftIsOn ? -bAcceleration : 0.0) + (rightIsOn ? bAcceleration : 0.0);
			yAcceleration = (upIsOn ? -bAcceleration : 0.0) + (downIsOn ? bAcceleration : 0.0);
			accelerationChanged = false;
		}
		if(fireChanged) {
			fireChanged = false;

			if(!fireIsOn) {

				ActionShot();
				/*	PlayerShot *shot = new PlayerShot(*this);
					shot->Init();
					Singleton::allFriends->RegisterObject(shot);*/
			}
		}
	}

}

void Player::ActionDoor() {

	if(door != NULL) {

		if(door->Enter(this)) {
		
			sfxPortal->Play();	
		}
		return;
	}

}

void Player::ActionJump() {

	if(!grounded) {

		if (doubleJumps <= 0) {

			return;
		}

		if (doubleJumpsNow > 0) {

			return;
		}
	}

	ySpeed = -yMaxSpeed;
	sfxJump->Play();

	if(!grounded && doubleJumps >= 1) {

		doubleJumps--;
		doubleJumpsNow++;
	}
}

void Player::ActionShot() {

	sfxStrongLaser->Play();
/*
	Projectile::Direction nextShotDirection;
	if(upIsOn && !downIsOn) {

		nextShotDirection = Projectile::up;
	} else if(downIsOn && !upIsOn && !grounded) {

		nextShotDirection = Projectile::down;
	} else {

		if(spriteFace->facing == SpriteFace::left) {

			nextShotDirection = Projectile::left;
		} else if(spriteFace->facing == SpriteFace::right) {

			nextShotDirection = Projectile::right;
		} else if(spriteFace->facing == SpriteFace::front) {

			nextShotDirection = Projectile::down;
		} else {

			cout << "facing = " << spriteFace->facing << endl;
		}
	}


	}else if(xSpeed > 0.0) {

		nextShotDirection = Projectile::right;
	} else if(xSpeed < 0.0) {

		nextShotDirection = Projectile::left;
	} else {

		nextShotDirection = Projectile::down;
	}*/

	PlayerShot* shot = new PlayerShot(*this, nextShotDirection, distance + shortDistance, power);
	shot->Init();
	Singleton::allFriends->RegisterObject(shot);
	distance--;
	if(distance < 0) {

		distance = 0;
	}
	power--;
	if(power < 0) {

		power = 0;
	}
}

void Player::Render() {

	this->AccelerableObject::Render();
}

void Player::ShowPowerUps() {

//	Sprite* spriteR = Singleton::spriteMap->Get("NUMBERS+R");
	Sprite* spriteG = Singleton::spriteMap->Get("NUMBERS+G");
	Sprite* spriteB = Singleton::spriteMap->Get("NUMBERS+B");

	sf::IntRect rect;

	rect.left = 410;
	rect.top = 20;
	rect.width = 8;
	rect.height = 8;

	spriteG->RenderCopy(&rect, distance);

	rect.left += 16;
	spriteB->RenderCopy(&rect, doubleJumps);
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
