#pragma once

#include "GameObject.h"

class CubeGameObject : public GameObject
{
public:
	CubeGameObject();
	virtual void update(float deltaTime) override {};
};

