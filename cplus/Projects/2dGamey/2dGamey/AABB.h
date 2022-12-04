#pragma once
#include "pch.h"

class AABB
{
	Rect m_box;
public:
	AABB(Rect rect);
	float getLength();
	float getWidth();
	float top();
	float left();
	float right();
	float bottom();

	static bool isBoxColliding(AABB& box1, AABB& box2);
	static bool isPointInside(Point point, AABB& box);
};
