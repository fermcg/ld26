#include "projectile.h"

Projectile::Projectile(const char* name, const char* objectId) : AccelerableObject(name, objectId) {

	direction = Projectile::up;
	isProjectile = true;
	gravity = false;
}
Projectile::~Projectile() {

}

void Projectile::HandleLogic() {

/*	if(y < -100.0 || y > 3000.0) {

		dead = true;
	}

	if(x < -100.0 || x > 3000.0) {

		dead = true;
	}*/

	this->AccelerableObject::HandleLogic();
}
