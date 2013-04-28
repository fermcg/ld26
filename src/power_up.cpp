#include "power_up.h"


PowerUp::PowerUp(const char* name, const char* objectId) : GameObject(name, objectId) {

	energy = 1;
	damage = 0;
}

PowerUp::~PowerUp() {
}

void PowerUp::Init() throw() {

	return this->GameObject::Init();
}

void PowerUp::Terminate() {

	return this->GameObject::Terminate();
}

void PowerUp::HandleLogic() {

	return this->GameObject::HandleLogic();
}
void PowerUp::OnCollision(GameObject& other) {

	return this->GameObject::OnCollision(other);
}
