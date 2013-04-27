#include "base_system.h"

#include <iostream>

using namespace std;

BaseSystem::BaseSystem(const char* name) {
	
	initialized = false;
	this->name = name;
}
BaseSystem::~BaseSystem() {
	
	if (initialized) {
		
		cerr << "BaseSystem [" << GetFullName() << "] destroyed with unfinished business" << endl;
	}
}
void BaseSystem::Init() {
	
	initialized = true;
}
void BaseSystem::Terminate() {
	
	initialized = false;
}

string BaseSystem::GetFullName() const {
	
	string fullName = name;
	fullName.append(".").append(objectId);
	
	return fullName;
}