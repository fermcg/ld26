#include <iostream>

#include "texture.h"
#include "exceptions.h"
#include "macros.h"
#include "singletons.h"
#include "ResourcePath.hpp"

using namespace std;
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

	texture = new sf::Texture();
	
	if (!image.loadFromFile(resourcePath() + fileName)) {

		cerr << "Error loading image file [" << objectId << "] [" << fileName << "]" << endl;
		THROWINFO(Exception::BadObject, fileName.c_str());
	}
	if (!texture->loadFromImage(image)) {
		
		cerr << "Error loading texture from image file [" << objectId << "] [" << fileName << "]" << endl;
		THROWINFO(Exception::BadObject, fileName.c_str());
	}

	w = texture->getSize().x;
	h = texture->getSize().y;

	this->BaseSystem::Init();
}

void Texture::Terminate() {

	if(texture != NULL) {

		delete texture;
		texture = NULL;
	}
	this->BaseSystem::Terminate();
}
