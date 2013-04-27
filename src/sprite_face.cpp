#include <iostream>
#include "sprite_face.h"
#include "singletons.h"
#include "exceptions.h"
#include "macros.h"

using namespace std;

SpriteFace::SpriteFace(const char* objectId) : BaseSystem("SpriteFace") {
	
	this->objectId = objectId;
	this->facing = SpriteFace::front;
}

SpriteFace::~SpriteFace() {
	
}

void SpriteFace::Init() {
	
}

void SpriteFace::Terminate() {
	
	MapOfFaces::iterator it;
	for(it = faces.begin(); it != faces.end(); it++) {
		
		delete it->second;
	}
	faces.clear();
}

void SpriteFace::RenderCopy(const SDL_Rect* destinyRect) throw() {

	this->GetSequence()->RenderCopy(destinyRect);
}
SpriteSequence* SpriteFace::GetSequence() throw() {

	MapOfFaces::iterator it;
	
	it = faces.find(facing);
	if(it == faces.end()) {
		
		cerr << "SpriteFace::GetSequence - face not found [" << facing << "]" << endl;
		THROWINFO(Exception::FaceNotFound, this->GetFullName().c_str());
	}
	return it->second;
}

void SpriteFace::RegisterFace(const Facing facing, const char* spriteId) throw() {
	
	MapOfFaces::iterator it;
	
	it = faces.find(facing);
	if(it != faces.end()) {
		
		delete it->second;
		faces.erase(it);
	}
	
	Sprite* sprite = Singleton::spriteMap->Get(spriteId);
	SpriteSequence* spriteSequence = sprite->InstanceSequence();
	faces[facing] = spriteSequence;
}
void SpriteFace::ChangeFace(const Facing facing) {
	this->facing = facing;
	this->GetSequence()->ResetFrame();
}
