#include "energy_bar.h"
#include "singletons.h"

const int EnergyBar::MaxEnergy = 5000;

EnergyBar::EnergyBar() : BaseSystem("EnergyBar") {

	maxEnergy = EnergyBar::MaxEnergy;
	energy = maxEnergy;
}

EnergyBar::~EnergyBar() {
}

void EnergyBar::Init() {

	this->BaseSystem::Init();

	greenBar = Singleton::spriteMap->Get("ENERGY+G");
	redBar = Singleton::spriteMap->Get("ENERGY+R");

	rect.x = 640 / 2 - greenBar->rect.w / 2;
	rect.y = 20;
	rect.w = 80;
	rect.h = 4;
}

void EnergyBar::Terminate() {

	this->BaseSystem::Terminate();
}

void EnergyBar::Render() {

	redBar->RenderCopy(&rect);

	SDL_Rect greenRect = rect;

	greenRect.w = (Uint16)((energy * (int)rect.w) / maxEnergy);
	greenBar->RenderCopy(&greenRect);
}

void EnergyBar::SetEnergy(const int energy) {

	if(energy > maxEnergy) {

		this->energy = maxEnergy;
	} else {

		this->energy = energy;
	}
}
