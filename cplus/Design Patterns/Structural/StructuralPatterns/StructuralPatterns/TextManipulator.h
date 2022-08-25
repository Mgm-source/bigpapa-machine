#pragma once
#include "Manipulator.h"
#include "TextShape.h"
class TextManipulator : public Manipulator {
public:
	TextManipulator(const TextShape*);
	TextManipulator(const TextShapeO*);
};

