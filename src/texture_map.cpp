#include <iostream>

#include "texture_map.h"
#include "singletons.h"
#include "exceptions.h"
#include "macros.h"

using namespace std;

TextureMap::TextureMap() : BaseSystem("TextureMap") {

}

TextureMap::~TextureMap() {
	
}

void TextureMap::Init() {

	this->LoadFile("SPRITES", "sprites.png");
	this->BaseSystem::Init();
}

void TextureMap::Terminate() {
	
	TextureMap::iterator it;
	for(it = this->begin(); it != this->end(); it++) {
		
		it->second->Terminate();
		delete it->second;
	}
	this->clear();
	this->BaseSystem::Terminate();
}

/*
void TextureMap::Load() {

	// Getting internal config map.
	const ConfigMap& configMap(config.Map());
	// Parsing
	ConfigMap::const_iterator itSection;
	for(itSection = configMap.begin(); itSection != configMap.end(); itSection++) {
		
		const string& sectionName(itSection->first);
		if (itSection->second == NULL) {
			
			cerr << "Invalid section at texture file: [" << sectionName << "]" << endl;
			THROWINFO(Exception::BadObject, sectionName.c_str());
		}
		const ConfigSection& section(*itSection->second);
		ConfigSection::const_iterator it;
		it = section.find("type");
		if (it == section.end()) {
			
			cerr << "Invalid texture object -> no type key: [" << sectionName << "]" << endl;
			THROWINFO(Exception::BadObject, sectionName.c_str());
		}
		
		const string& configType(it->second);
		if (configType == "file") {
			
			string path;
			
			if (!section.GetIfExists("path")) {
								
				cerr << "Invalid texture object -> no file path for [" << sectionName << "]" << endl;
				THROWINFO(Exception::BadObject, sectionName.c_str());
			}
			LoadFile(sectionName, path);
		} else if (configType == "sprite") {
			
			string source;
			if (!section.GetIfExists("source")) {
				
				cerr << "Invalid texture object -> no source file for [" << sectionName << "]" << endl;
				THROWINFO(Exception::BadObject, sectionName.c_str());
			}
			
			string rect;
			if (!section.GetIfExists("rect")) {
				
				cerr << "Invalid texture object -> no rect for [" << sectionName << "]" << endl;
				THROWINFO(Exception::BadObject, sectionName.c_str());
			}
			LoadSprite(sectionName, source, rect);
		}
	}
}*/
Texture* TextureMap::Get(const char* textureId) {
	
	TextureMap::iterator it;
	it = this->find(textureId);
	if(it == this->end()) {
		
		cerr << "Error getting [" << textureId << "] texture" << endl;
		THROWINFO(Exception::TextureNotFound, textureId);
	}
	
	return it->second;
}
void TextureMap::LoadFile(const char* textureId, const char* path) {
	
	TextureMap::const_iterator it;
	it = this->find(textureId);
	
	if(it != this->end()) {
		
		cerr << "Invalid texture object -> [" << textureId << "] [" << path << "]"
			<< "file already loaded.";
		THROWINFO(Exception::BadObject, textureId);
	}
	Texture* texture = new Texture(path, textureId);
	texture->Init();
	
	(*this)[textureId] = texture;
}
