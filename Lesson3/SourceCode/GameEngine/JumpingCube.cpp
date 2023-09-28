#include "JumpingCube.h"

JumpingCube::JumpingCube(float floorLevel) : m_velocity(10.0f), m_floorLevel(floorLevel) {};

void JumpingCube::update(float deltaTime)
{
	m_vPosition[1] += deltaTime * m_velocity;
	m_pRenderProxy->SetPosition(m_vPosition);

	if (m_vPosition[1] <= m_floorLevel)
		m_velocity = 10.0f;

	m_velocity -= deltaTime * 10.0f;
}
