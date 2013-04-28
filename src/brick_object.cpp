#include "brick_object.h"

const int BrickObject::Width = 8;
const int BrickObject::Height = 8;

BrickObject::BrickObject(const char* name, const char* objectId) : GameObject(name, objectId) {

	xSize = 1;
	ySize = 1;
	unbreakable = true;
	solid = true;

	boundingBox.x = 0;
	boundingBox.y = 0;
	boundingBox.w = BrickObject::Width;
	boundingBox.h = BrickObject::Height;
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


	SDL_Rect rect;

	rect.w = BrickObject::Width;
	rect.h = BrickObject::Height;


	int i, j;
	rect.y = (Sint16)(int)y;
	for(j = 0; j < ySize; j++) {
		
		rect.x = (Sint16)(int)x;
		for(i = 0; i < xSize; i++) {

			this->spriteFace->RenderCopy(&rect);
			rect.x += BrickObject::Width;
		}
		rect.y += BrickObject::Height;
	}
	this->spriteFace->GetSequence()->IncrementSequence();
}

void BrickObject::HandleLogic() {

}

void BrickObject::OnCollision() {

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

		this->boundingBox.w += other->w;
		return true;
	}

	if(this->y + this->h == other->y && this->x == other->x && this->w == other->w) {

		// can Merge in y axis.
		this->h += other->h;
		this->ySize += other->ySize;

		this->boundingBox.h += other->h;
		return true;
	}

	return false;
}

