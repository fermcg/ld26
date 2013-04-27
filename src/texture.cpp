#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include "texture.h"
#include "exceptions.h"
#include "macros.h"
#include "singletons.h"

Texture::Texture(const char* fileName, const char* textureId) : BaseSystem("Texture"){
	
	this->objectId = textureId;
	this->fileName = fileName;
	this->texture = NULL;
	this->w = 0;
	this->h = 0;
}
Texture::~Texture() {
	
}

void Texture::Init() {

	SDL_Surface* surface = IMG_Load(fileName.c_str());
	
	if(surface == NULL) {
		
		cerr << "Error loading image file [" << objectId << "] [" << fileName << "]: [" << IMG_GetError() << "]" << endl;
		THROWINFO(Exception::BadObject, fileName.c_str());
	}
	
	texture = SDL_CreateTextureFromSurface(Singleton::screen->renderer, surface);
	
	SDL_FreeSurface(surface);
	
	if(texture == NULL) {
		
		cerr << "Error creating texture from image file [" << objectId << "] [" << fileName << "]: [" << SDL_GetError() << "]" << endl;
		THROWINFO(Exception::BadObject, objectId.c_str());
	}
	
	Uint32 format = 0;
	int access = 0;
	
	int r = SDL_QueryTexture(texture, &format, &access, &w, &h);
	if(r != 0) {
		cerr << "Error querying texture from image file [" << objectId << "] [" << fileName << "]: [" << SDL_GetError() << "]" << endl;
		SDL_DestroyTexture(texture);
		texture = NULL;
		THROWINFO(Exception::BadObject, objectId.c_str());
	}	
	this->BaseSystem::Init();
}

void Texture::Terminate() {
	
	if(texture != NULL) {
		
		SDL_DestroyTexture(texture);
		texture = NULL;
	}
	this->BaseSystem::Terminate();
}
