#include "brick_object.h"

const int BrickObject::Width = 8;
const int BrickObject::Height = 8;

BrickObject::BrickObject(const char* name, const char* objectId) : GameObject(name, objectId) {

	nx = 1;
	ny = 1;
}

BrickObject::~BrickObject() {
}
	
void BrickObject::Init() throw() {

	this->GameObject::Init();
}

void BrickObject::Terminate() {

	this->GameObject::Terminate();
}

void BrickObject::Render() {

	int i, j;

}

void BrickObject::HandleLogic() {

}

void BrickObject::OnCollision() {

}

bool BrickObject::Merge(GameObject* other) {

	return Merge(dynamic_cast< BrickObject * >(other));
}

bool BrickObject::Merge(BrickObject* other) {

	if(this->x + this->w + 1 == other->x && this->y == other->y && this->h == other->h) {

		// can Merge in x axis.
		this->w += other->w;
		this->nx += other->nx;

		this->boundingBox.w += other->w;
		return true;
	}

	if(this->y + this->h + 1 == other->y && this->x == other->x && this->w == other->w) {

		// can Merge in y axis.
		this->h += other->x;
		this->ny += other->ny;

		this->boundingBox.h += other->h;
		return true;
	}

	return false;
}

