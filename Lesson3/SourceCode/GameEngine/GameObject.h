#pragma once

#include "Common.h"
#include "RenderProxy.h"

class GameObject
{
public:
	GameObject() = default;

	~GameObject()
	{
		delete m_pRenderProxy;
	}

	virtual void SetPosition(float x, float y, float z);
	virtual void update(float deltaTime) {};

	RenderProxy* const GetRenderProxy() { return m_pRenderProxy; }
protected:
	RenderProxy* m_pRenderProxy;

	float m_vPosition[3];
};

