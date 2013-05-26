#include <iostream>
#include "player.h"
#include "player_shot.h"
#include "singletons.h"
#include "number_power.h"
#include "door_object.h"

using namespace std;

Player::Player() : AccelerableObject("Player", "Player") {

	bAcceleration = 0.07;
	gAccelerationBase = 0.20;
	jAcceleration = 0.10;

	// Accelerable vars

	xMinSpeed = 0.0;
	xMaxSpeed = 2.0;
	yMinSpeed = 0.0;
	yMaxSpeed = 3.0;

	xBreaking = 0.13;
	yBreaking = 0.10;

	fireIsOn = false;
	leftIsOn = false;
	rightIsOn = false;
	upIsOn = false;
	downIsOn = false;
	jumpIsOn = false;

	blinker = false;

	accelerationChanged = false;
	fireChanged = false;
	jumpChanged = false;
	untouchable = false;

	untouchableMiliSeconds = 4000;
	blinkMiliSeconds = 100;
	untouchableSoundMiliSeconds = untouchableMiliSeconds / 4;

	boundingBox.left = 1;
	boundingBox.top = 4;
	boundingBox.width = 5;
	boundingBox.height = 12;

	lastGroundedX = 0;
	lastGroundedX = 0;

	lifes = 3;

	damage = 2000;

	sfxStep = NULL;
	sfxStrongLaser = NULL;
	sfxJump = NULL;
	sfxDeath = NULL;
	sfxPowerup = NULL;
	sfxPortal = NULL;
	sfxUntouchable = NULL;
	door = NULL;
	walking = false;
	isPlayer = true;


	maxEnergy = 5000;
	maxPower = 9;
	maxDistance = 10;
	maxDoubleJumps = 10;

	energy = maxEnergy;
	lastEnergy = energy;
	power = 0;
	distance = 0;
	doubleJumps = 0;
	doubleJumpsNow = 0;

	nextLife = 0;

	shortDistance = 4;
	nextShotDirection = Projectile::down;
	nextLife = 20000;
}

Player::~Player() {

}

void Player::Ressurrect() {

	dead = false;
	lifes = 3;
	nextLife = 20000;
	Recover();
}

void Player::Recover() {

	dead = false;
	energy = maxEnergy;
	lastEnergy = energy;
	distance = 0;
	doubleJumps = 0;
	power = 0;

	xSpeed = 0.0;
	ySpeed = 0.0;

	untouchable = false;
	blinker = false;
//	x = lastGroundedX;
//	y = lastGroundedY;
}

void Player::Init() throw() {

	this->AccelerableObject::Init();

	sfxStep = Singleton::soundEffectsMap->Get("PLAYER+STEP");
	sfxStrongLaser = Singleton::soundEffectsMap->Get("STRONGLASER");
	sfxJump = Singleton::soundEffectsMap->Get("PLAYER+JUMP");
	sfxDeath = Singleton::soundEffectsMap->Get("PLAYER+DEATH");
	sfxPowerup = Singleton::soundEffectsMap->Get("POWERUP");
	sfxPortal = Singleton::soundEffectsMap->Get("PORTAL");
	sfxUntouchable = Singleton::soundEffectsMap->Get("UNTOUCHABLE");
	sfxNewLife = Singleton::soundEffectsMap->Get("NEWLIFE");
	sfxFullEnergy = Singleton::soundEffectsMap->Get("FULLENERGY");
	sfxHurt = Singleton::soundEffectsMap->Get("HURT");

	SetNeverLeaveArea(false);
	x = minX + (maxX - minX) / 2.0;
	y = maxY;

	Sprite* sprite = this->spriteFace->GetSequence()->GetSprite();
	if (sprite->sRect.width != 8) {
		boundingBox.width += sprite->sRect.width - 8;
	}
	if (sprite->sRect.height != 16) {
		boundingBox.height += sprite->sRect.height - 16;
	}
}

void Player::Terminate() {

	this->AccelerableObject::Terminate();
}

void Player::OnCollision(GameObject& other) {

	if (energy < 0) {

		if (!dead) {

			untouchable = false;
			blinker = false;
			sfxDeath->Play();
			spriteFace->ChangeFace(SpriteFace::dying);
			sfxStep->Stop();
			lifes--;
			dead = true;
			Singleton::screen->TempZoomOut();
			if (lifes >= 0) {

				Singleton::gameLoop->ReloadStage();
			} else {

				Singleton::gameLoop->GameOver();
			}
			return;
		}
	} else {

		if (untouchable) {

			energy = lastEnergy;
		} else if (energy < lastEnergy) {

			lastEnergy = energy;
			xSpeed = (xSpeed < 0.0 ? 0.8 * xMaxSpeed : (xSpeed > 0.0 ? -xMaxSpeed * 0.8 : 0.0));
			//xSpeed = -xSpeed;

			ySpeed -= yMaxSpeed * 0.7;
			if (ySpeed < -yMaxSpeed) {

				ySpeed = -yMaxSpeed;
			}
			sfxHurt->Play();
			untouchable = true;
			clockUntouchable.restart();
			clockBlink.restart();
			clockUntouchableSound.restart();
			untouchableSoundMiliSeconds = untouchableMiliSeconds / 8;
			//sfxUntouchable->Play();
		}
	}
	if(other.isDoor) {

		door = reinterpret_cast< DoorObject* >(&other);
	}
}

bool Player::CheckCollision(const GameObject& other) {

	if (untouchable && !other.lethal && other.isHurting) {

		return false;
	}

	return AccelerableObject::CheckCollision(other);
}

void Player::HandleLogic() {

	door = NULL;
	
	if (dead) {

		return;
	}

	if (Singleton::gameLoop->score > nextLife) {

		LifeUp();
		nextLife += 40000;
	}
	if (untouchable) {

		if (clockUntouchable.getElapsedTime().asMilliseconds() >= untouchableMiliSeconds) { // end of untouchable...

			untouchable = false;
			blinker = false;
			//sfxUntouchable->Stop();
		} else {
			if (clockBlink.getElapsedTime().asMilliseconds() >= (blinkMiliSeconds < untouchableSoundMiliSeconds ? blinkMiliSeconds : untouchableSoundMiliSeconds)) { // change blinking state...

				blinker = !blinker;
				clockBlink.restart();
			}
			if (clockUntouchableSound.getElapsedTime().asMilliseconds() >= untouchableSoundMiliSeconds) {

				sfxUntouchable->Stop();
				sfxUntouchable->Play();
				untouchableSoundMiliSeconds = (untouchableMiliSeconds - clockUntouchable.getElapsedTime().asMilliseconds()) / 8;
				if (untouchableSoundMiliSeconds < 50) {

					untouchableSoundMiliSeconds = 50;
				}
				clockUntouchableSound.restart();
			}
		}
	}
	if(xAcceleration > 0.0) {

		if (grounded) {
			spriteFace->ChangeFace(SpriteFace::right);
		} else {
			spriteFace->ChangeFace(SpriteFace::alt_right);
		}
	} else if(xAcceleration < 0.0) {
		
		if (grounded) {
			spriteFace->ChangeFace(SpriteFace::left);
		} else {
			spriteFace->ChangeFace(SpriteFace::alt_left);
		}
	} else if(downIsOn || xAcceleration == 0.0) {

		if (grounded) {
			spriteFace->ChangeFace(SpriteFace::front);
		} else {
			spriteFace->ChangeFace(SpriteFace::alt_front);
		}
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

	if (holdingJump) {

		gAcceleration = gAccelerationBase - jAcceleration;
	} else {

		gAcceleration = gAccelerationBase;
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
//		lastGroundedX = x;
//		lastGroundedY = y;
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
	//Singleton::gameLoop->score += other.scoreValue;
	sfxPowerup->Play();
}

void Player::LifeUp() {

	lifes++;
	if (lifes >= 100) {
		lifes = 99;
	} else {
		sfxNewLife->Play();
	}
}

void Player::EnergyUp(const int energy) {

	this->energy += energy;
	if (this->energy > maxEnergy) {

		this->energy = maxEnergy;
	}
	this->lastEnergy = this->energy;

	sfxFullEnergy->Play();
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

	SpriteFace* face = CreateWalkingCharFace("PLAYER");

	if (face != NULL) {

		face->SetBlinker(&blinker);
	}
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
				jumpChanged = true;

				if (!set) {

					holdingJump = false;
				}
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
		if(jumpChanged) {

			if (jumpIsOn) {

				ActionJump();
			}
			jumpChanged = false;
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

	if (dead) {

		return;
	}

	if(!grounded) {

		if (doubleJumps <= 0) {

			return;
		}

		if (doubleJumpsNow > 0) {

			return;
		}
	}

	holdingJump = true;
	ySpeed = -yMaxSpeed;
	sfxJump->Play();
	Singleton::screen->TempZoomOut();

	if(!grounded && doubleJumps >= 1) {

		doubleJumps--;
		doubleJumpsNow++;
	}
}

void Player::ActionShot() {

	if (dead) {

		return;
	}

	sfxStrongLaser->Play();
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

bool Player::IsDying() {

	return sfxDeath->IsPlaying();
}
