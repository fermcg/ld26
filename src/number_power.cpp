#include "number_power.h"
#include "player.h"

NumberPower::NumberPower(const Color color, const int number) : PowerUp("NumberPower", "NumberPower") {

	this->color = color;
	this->number = number;

	boundingBox.left = 2;
	boundingBox.top = 1;
	boundingBox.width = 4;
	boundingBox.height = 6;
	
	scoreValue = number * 100;
}

NumberPower::~NumberPower() {
}

void NumberPower::Init() throw() {

	this->PowerUp::Init();
}

void NumberPower::Terminate() {

	this->PowerUp::Terminate();
}

void NumberPower::HandleLogic() {

	this->PowerUp::HandleLogic();
}

void NumberPower::OnCollision(GameObject& other) {

	if(other.isPlayer) {

		(reinterpret_cast< Player& >(other)).GetNumberPower(*this);
	} else if(other.isProjectile) {
	}

	this->PowerUp::OnCollision(other);
}

SpriteFace* NumberPower::CreateSpriteFace() {

	SpriteFace* face = new SpriteFace("Number Power Face");

	switch(color) {

		case NumberPower::red:
			face->RegisterFace(SpriteFace::front, "NUMBERS+R");
			break;
		case NumberPower::green:
			face->RegisterFace(SpriteFace::front, "NUMBERS+G");
			break;
		case NumberPower::blue:
			face->RegisterFace(SpriteFace::front, "NUMBERS+B");
			break;
		default:
			delete face;
			return NULL;
	}

	face->GetSequence()->SetRenderingMode(SpriteSequence::single_frame);
	face->GetSequence()->ResetFrame(number);

	return face;
}
