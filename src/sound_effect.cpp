#include <iostream>

#include "sound_effect.h"
#include "exceptions.h"
#include "macros.h"

using namespace std;

SoundEffect::SoundEffect(const char* fileName, const char* soundId) : BaseSystem("SoundEffect") {

	this->fileName = fileName;
	this->objectId = soundId;
	this->sample = NULL;
}

SoundEffect::~SoundEffect() {

}

void SoundEffect::Init() {

	sample = Mix_LoadWAV(fileName.c_str());

	if(sample == NULL) {

		cerr << "Error loading sound file [" << objectId << "] [" << fileName << "]: [" << Mix_GetError() << "]" << endl;
		THROWINFO(Exception::BadObject, fileName.c_str());
	}
	this->BaseSystem::Init();
}

void SoundEffect::Terminate() {

	if(sample != NULL) {

		Mix_FreeChunk(sample);
		sample = NULL;
	}
	this->BaseSystem::Terminate();
}

int SoundEffect::Play(const int channelId, const int loops) {

	int playChannel = Mix_PlayChannel(channelId, sample, loops);
	if(playChannel == -1) {

		cerr << "Error playing sound chunk [" << objectId << "] on channel ["
			<< channelId << "] loops [" << loops << "] [" << Mix_GetError() << "]" << endl;
		THROWINFO(Exception::BadAudioPlay, objectId.c_str());
	}

	return playChannel;
}

int SoundEffect::Start(const int channelId) {

	return Play(channelId, -1);
}

void SoundEffect::Stop(const int channelId) {

	Mix_HaltChannel(channelId);
}
