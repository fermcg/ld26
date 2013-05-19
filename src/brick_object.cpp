#include "brick_object.h"

const int BrickObject::Width = 8;
const int BrickObject::Height = 8;

BrickObject::BrickObject(const char* name, const char* objectId) : GameObject(name, objectId) {

	xSize = 1;
	ySize = 1;
	unbreakable = true;
	solid = true;
	stationary = true;
	damage = 0;

	boundingBox.left = 0;
	boundingBox.top = 0;
	boundingBox.width = BrickObject::Width;
	boundingBox.height = BrickObject::Height;

	xAdjust = 2.0;
}

BrickObject::~BrickObject() {
}

void BrickObject::Init() throw() {

	this->GameObject::Init();
	this->spriteFace->GetSequence()->LockSequence();
}

void BrickObject::Terminate() {

	this->GameObject::Terminate();
}

void BrickObject::Render() {


	sf::IntRect rect;

	rect.width = BrickObject::Width;
	rect.height = BrickObject::Height;


	int i, j;
	rect.top = (int)y;
	for(j = 0; j < ySize; j++) {
		
		rect.left = (int)x;
		for(i = 0; i < xSize; i++) {

			this->spriteFace->RenderCopy(&rect);
			rect.left += BrickObject::Width;
		}
		rect.top += BrickObject::Height;
	}
	this->spriteFace->GetSequence()->IncrementSequence();
}

void BrickObject::HandleLogic() {

	this->GameObject::HandleLogic();
}

void BrickObject::OnCollision(GameObject& other) {

	this->GameObject::OnCollision(other);
}

bool BrickObject::Merge(GameObject* other) {

	if(this->GetFullName() != other->GetFullName()) {

		return false;
	}

	return Merge(dynamic_cast< BrickObject * >(other));
}

bool BrickObject::Merge(BrickObject* other) {

	if(this->x + this->w == other->x && this->y == other->y && this->h == other->h) {

		// can Merge in x axis.
		this->w += other->w;
		this->xSize += other->xSize;

		this->boundingBox.width += other->w;
		return true;
	}

	if(this->y + this->h == other->y && this->x == other->x && this->w == other->w) {

		// can Merge in y axis.
		this->h += other->h;
		this->ySize += other->ySize;

		this->boundingBox.height += other->h;
		return true;
	}

	return false;
}

