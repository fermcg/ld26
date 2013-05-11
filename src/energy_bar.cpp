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

	rect.left = Singleton::screen->window->getSize().x / 2 - greenBar->rect.width / 2;
	rect.top = 10;
	rect.width = 80;
	rect.height = 4;
}

void EnergyBar::Terminate() {

	this->BaseSystem::Terminate();
}

void EnergyBar::Render() {

	redBar->RenderCopy(&rect);

	sf::IntRect greenRect = rect;

	greenRect.width = (int)((energy * (int)rect.width) / maxEnergy);
	greenBar->RenderCopy(&greenRect);
}

void EnergyBar::SetEnergy(const int energy) {

	if(energy > maxEnergy) {

		this->energy = maxEnergy;
	} else {

		this->energy = energy;
	}
}
