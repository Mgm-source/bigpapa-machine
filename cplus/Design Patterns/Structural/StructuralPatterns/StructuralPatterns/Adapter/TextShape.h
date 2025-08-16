#pragma once
#include "Shape.h"
#include "TextView.h"
class TextShape : public Shape , private TextView {
public:
	TextShape() = default;
	// adaptor class
	void BoundingBox(Point& bottomLeft, Point& topRight) const;
	Manipulator* CreateManipulator() const;
	bool isEmpty() const;

};

class TextShapeO : public Shape {
	TextView* _textView;
public:
	TextShapeO(TextView* textView);
	// adaptor class
	void BoundingBox(Point& bottomLeft, Point& topRight) const;
	Manipulator* CreateManipulator() const;
	bool isEmpty() const;

};

