#include <iostream>

#include "sound_effect.h"
#include "exceptions.h"
#include "macros.h"
#include "ResourcePath.hpp"

using namespace std;

SoundEffect::SoundEffect(const char* fileName, const char* soundId) : BaseSystem("SoundEffect") {

	this->fileName = fileName;
	this->objectId = soundId;
	this->buffer = NULL;
	this->sound = NULL;
}

SoundEffect::~SoundEffect() {

}

void SoundEffect::Init() {

	buffer = new sf::SoundBuffer();
	if (!buffer->loadFromFile(resourcePath() + fileName)) {

		cerr << "Error loading sound file [" << objectId << "] [" << fileName << "]:" << endl;
		THROWINFO(Exception::BadObject, fileName.c_str());
	}

	sound = new sf::Sound(*buffer);
	this->BaseSystem::Init();
}

void SoundEffect::Terminate() {

	if(sound != NULL) {

		delete sound;
		sound = NULL;
	}
	if(buffer != NULL) {

		delete buffer;
		buffer = NULL;
	}
	this->BaseSystem::Terminate();
}

void SoundEffect::Play() {

	sound->setLoop(false);
	sound->stop();
	sound->play();
}

void SoundEffect::Start() {
	
	sound->setLoop(true);
	sound->play();
}

void SoundEffect::Stop() {

	sound->stop();
}
