#pragma once
#include "CubeGameObject.h"
#include "InputHandler.h"

class ControllableCube : public CubeGameObject
{
public:
	ControllableCube(InputHandler* ih);
	virtual void update(float deltaTime) override;

private:
	InputHandler* m_inputHandler;
};

