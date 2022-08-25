#pragma once
#include "Point.h"
#include "Manipulator.h"
class Shape {
public:
	Shape()= default;
	virtual void BoundingBox(Point& bottomLeft, Point& topRight) const;
	virtual Manipulator* CreateManipulator() const;
};

