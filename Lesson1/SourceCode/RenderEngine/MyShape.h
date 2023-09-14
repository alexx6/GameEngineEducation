#pragma once

#include "RenderObject.h"
namespace
{
	struct MyPosColorVertex
	{
		float m_x;
		float m_y;
		float m_z;
		uint32_t m_abgr;
	};
};

class MyShape : public RenderObject
{
public:
	MyShape();
	inline static const MyPosColorVertex s_cubeVertices[] =
	{
		{0.0f, 0.0f, 1.0f, 0xffffffff},
		{0.54f, 0.0f, 0.84f, 0xff0fff00},
		{0.91f, 0.0f, 0.42f, 0xffffffff},
		{0.99f, 0.0f, -0.14f, 0xff0f00ff},
		{0.76f, 0.0f, -0.65f, 0xffffffff},
		{0.28f, 0.0f, -0.96f, 0xff00ffff},
		{-0.28f, 0.0f, -0.96f, 0xffffffff},
		{-0.76f, 0.0f, -0.65f, 0xff00f00f},
		{-0.99f, 0.0f, -0.14f, 0xffffffff},
		{-0.91f, 0.0f, 0.42f, 0xff0ff0f0},
		{-0.54f, 0.0f, 0.84f, 0xffffffff},
		{-0.0f, 0.0f, 1.0f, 0xfff00f0f},
		{0.0f, 5.0f, 0.0f, 0xffffffff},
	};

	inline static const uint16_t s_cubeTriList[] =
	{
		0, 12, 1,
		1, 12, 2,
		2, 12, 3,
		3, 12, 4,
		4, 12, 5,
		5, 12, 6,
		6, 12, 7,
		7, 12, 8,
		8, 12, 9,
		9, 12, 10,
		10, 12, 11,
		11, 12, 0,
		0, 1, 11,
		11, 1, 10,
		9, 10, 1,
		9, 1, 2,
		8, 9, 2,
		8, 2, 3,
		7, 8, 3,
		7, 3, 4,
		6, 7, 4,
		6, 4, 5
	};
};

