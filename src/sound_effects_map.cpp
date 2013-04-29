#include <iostream>

#include "sound_effects_map.h"
#include "exceptions.h"
#include "macros.h"

using namespace std;

SoundEffectsMap::SoundEffectsMap() : BaseSystem("SoundEffectsMap") {

}

SoundEffectsMap::~SoundEffectsMap() {

}

void SoundEffectsMap::Init() {
	this->BaseSystem::Init();

	LoadSound("PLAYER+STEP", "Step.wav");
	LoadSound("STRONGLASER", "StrongLaser.wav");
	LoadSound("PLAYER+JUMP", "Jump.wav");
	LoadSound("PLAYER+DEATH", "Death.wav");
	LoadSound("POWERUP", "GrabItem.wav");
	LoadSound("PORTAL", "Portal.wav");
}

void SoundEffectsMap::Terminate() {

	SoundEffectsMap::iterator it;
	for(it = this->begin(); it != this->end(); it++) {

		it->second->Terminate();
		delete it->second;
	}
	this->clear();
	this->BaseSystem::Terminate();
}

SoundEffect* SoundEffectsMap::Get(const char* soundId) {

	SoundEffectsMap::iterator it;
	it = this->find(soundId);
	if(it == this->end()) {

		cerr << "Error getting [" << soundId << "] sound" << endl;
		THROWINFO(Exception::SoundNotFound, soundId);
	}

	return it->second;
}

void SoundEffectsMap::LoadSound(const char* soundId, const char* fileName) {

	SoundEffectsMap::const_iterator it;
	it = this->find(soundId);
	if(it != this->end()) {

		cerr << "Invalid sound object -> [" << soundId << "] sound already loaded.";
		THROWINFO(Exception::BadObject, soundId);		
	}

	SoundEffect* soundEffect = new SoundEffect(fileName, soundId);
	soundEffect->Init();
	(*this)[soundId] = soundEffect;
}
