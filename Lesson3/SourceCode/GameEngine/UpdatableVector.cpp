#include "UpdatableVector.h"

void UpdatableVector::update(float deltaTime)
{
	for (GameObject* obj : *this)
		obj->update(deltaTime);
}
