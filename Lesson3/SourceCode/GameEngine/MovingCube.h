#pragma once
#include "CubeGameObject.h"
class MovingCube : public CubeGameObject
{
public:
    MovingCube();
    virtual void update(float deltaTime) override;
    virtual void SetPosition(float x, float y, float z) override;

private:
    //Total is different for each cube because they can be created at different time points]
    float m_totalTime;
    float m_anchorPointZ;
};

