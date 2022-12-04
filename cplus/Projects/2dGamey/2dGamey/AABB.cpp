#include "pch.h"
#include "AABB.h"

AABB::AABB(Rect rect) : m_box { rect }
{

}

float AABB::getLength()
{
	return m_box.bottomRight.x - m_box.topLeft.x;
}

float AABB::getWidth()
{
	return m_box.bottomRight.y - m_box.topLeft.y;
}

float AABB::top()
{
	return m_box.topLeft.y;
}

float AABB::left()
{
	return m_box.topLeft.x;
}

float AABB::right()
{
	return m_box.bottomRight.x;
}

float AABB::bottom()
{
	return m_box.bottomRight.y;
}

bool AABB::isBoxColliding(AABB& box1, AABB& box2)
{
	return box1.left() <= box2.right() && 
		   box1.right() >= box2.left() &&
		   box1.top() <= box2.bottom() &&
		   box1.bottom() >= box2.top();
}

bool AABB::isPointInside(Point point, AABB& box)
{
 return point.x <= box.right() &&
		point.x >= box.left() &&
		point.y <= box.bottom() &&
		point.y >= box.top();
}
