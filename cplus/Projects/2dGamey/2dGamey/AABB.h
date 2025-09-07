#pragma once
#include "Utility.h"

class AABB
{
	Rect m_box;
public:
	AABB(Rect rect);
	float getLength() const;
	float getWidth() const;
	float top() const;
	float left() const;
	float right() const;
	float bottom() const;

	static bool isBoxColliding(AABB& box1, AABB& box2);
	static bool isPointInside(Point point, AABB& box);
};
