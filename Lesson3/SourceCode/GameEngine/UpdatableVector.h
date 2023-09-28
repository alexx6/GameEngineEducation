#pragma once
#include <vector>
#include "GameObject.h"

class UpdatableVector : public std::vector<GameObject*>
{
public:
	void update(float deltaTime);
};

