#include "new_life.h"
#include "player.h"

NewLife::NewLife() : PowerUp("NumberPower", "NumberPower") {

	boundingBox.left = 2;
	boundingBox.top = 2;
	boundingBox.width = 6;
	boundingBox.height = 4;
	
	scoreValue = 2000;
}

NewLife::~NewLife() {
}

void NewLife::Init() throw() {

	this->PowerUp::Init();
}

void NewLife::Terminate() {

	this->PowerUp::Terminate();
}

void NewLife::HandleLogic() {

	this->PowerUp::HandleLogic();
}

void NewLife::OnCollision(GameObject& other) {

	if(other.isPlayer) {

		(reinterpret_cast< Player& >(other)).LifeUp();
	} else if(other.isProjectile) {
		return;
	}

	this->PowerUp::OnCollision(other);
}

SpriteFace* NewLife::CreateSpriteFace() {

	SpriteFace* face = new SpriteFace("New Life Face");

	face->RegisterFace(SpriteFace::front, "NEWLIFE");

	return face;
}
