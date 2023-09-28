#include "MovingCube.h"

MovingCube::MovingCube() : m_totalTime(0) {};

void MovingCube::update(float deltaTime)
{
	m_totalTime += deltaTime;
	m_vPosition[2] = m_anchorPointZ + sin(m_totalTime * 3.0f) * 5;
	m_pRenderProxy->SetPosition(m_vPosition);
}

void MovingCube::SetPosition(float x, float y, float z)
{
	GameObject::SetPosition(x, y, z);
	m_anchorPointZ = z;
}
