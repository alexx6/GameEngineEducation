#pragma once
#include "CubeGameObject.h"
class JumpingCube : public CubeGameObject
{
public:
    JumpingCube(float floorLevel);
    virtual void update(float deltaTime) override;

private:
    float m_velocity;
    float m_floorLevel;
};

