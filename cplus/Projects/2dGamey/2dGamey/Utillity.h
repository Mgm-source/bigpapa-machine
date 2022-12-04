#pragma once
#include "pch.h"
struct Point
{
	float x, y;
};

struct Rect
{
	Point topLeft;
	Point bottomRight;
};

enum class MouseEvents
{
	NONE = 0,
	LEFTDOWN,
	LEFTUP,
	RIGHTDOWN,
	RIGHTUP
};