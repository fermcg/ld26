#include "ice_brick.h"

IceBrick::IceBrick() : BrickObject("IceBrick", "IceBrick") {
	
//	preRender = true;
	xAdjust = 0.4;
	yAdjust = 1.0;
	xAdjustAcceleration = 0.8;
	yAdjustAcceleration = 1.0;

	smartBricks = true;
}

IceBrick::~IceBrick() {

}

void IceBrick::Init() throw() {

	this->GameObject::Init();
}

void IceBrick::Terminate() {

	this->GameObject::Terminate();
}

SpriteFace* IceBrick::CreateSpriteFace() {

	return CreateSmartBricksFace("SMART+ICE");
}
