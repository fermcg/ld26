#include "projectile.h"

Projectile::Projectile(const char* name, const char* objectId, const char* spriteId) : AccelerableObject(name, objectId, spriteId) {
	
}
Projectile::~Projectile() {
	
}

void Projectile::HandleLogic() {
	
	if(y < -100.0 || y > 3000.0) {
		
		dead = true;
	}
	
	this->AccelerableObject::HandleLogic();
}
