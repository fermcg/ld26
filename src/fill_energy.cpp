#include "fill_energy.h"
#include "player.h"

FillEnergy::FillEnergy(const char* fillEnergySprite, const int energyAmmount) : PowerUp("FillEnergy", "FillEnergy") {

	boundingBox.left = 1;
	boundingBox.top = 1;
	boundingBox.width = 6;
	boundingBox.height = 6;
	
	scoreValue = energyAmmount / 10;
	this->energyAmmount = energyAmmount;
	this->fillEnergySprite = fillEnergySprite;
}

FillEnergy::~FillEnergy() {
}

void FillEnergy::Init() throw() {

	this->PowerUp::Init();
}

void FillEnergy::Terminate() {

	this->PowerUp::Terminate();
}

void FillEnergy::HandleLogic() {

	this->PowerUp::HandleLogic();
}

void FillEnergy::OnCollision(GameObject& other) {

	if(other.isPlayer) {

		(reinterpret_cast< Player& >(other)).EnergyUp(energyAmmount);
	} else if(other.isProjectile) {
		return;
	}

	this->PowerUp::OnCollision(other);
}

SpriteFace* FillEnergy::CreateSpriteFace() {

	SpriteFace* face = new SpriteFace("Fill Energy Face");

	face->RegisterFace(SpriteFace::front, fillEnergySprite.c_str());

	return face;
}
