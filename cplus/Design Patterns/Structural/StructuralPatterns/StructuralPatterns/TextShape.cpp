#include "TextShape.h"
#include "TextManipulator.h"

void TextShape::BoundingBox(Point& bottomLeft, Point& topRight) const
{
	float bottom = 0.0f, left = 0.0f , width = 0.0f , height = 0.0f;
	
	GetOrigin(bottom, left);
	GetExtent(width,height );

	bottomLeft = Point();
	topRight = Point();
}

Manipulator* TextShape::CreateManipulator() const
{
	return new TextManipulator(this);
}

bool TextShape::isEmpty() const
{
	return TextView::isEmpty();
}

TextShapeO::TextShapeO(TextView* textView) : _textView {textView }
{
}

void TextShapeO::BoundingBox(Point& bottomLeft, Point& topRight) const
{
	float bottom = 0.0f, left = 0.0f, width = 0.0f, height = 0.0f;

	_textView->GetOrigin(bottom, left);
	_textView->GetExtent(width, height);

	bottomLeft = Point();
	topRight = Point();
}

Manipulator* TextShapeO::CreateManipulator() const
{
	return new TextManipulator(this);
}

bool TextShapeO::isEmpty() const
{
	return _textView->isEmpty();
}
