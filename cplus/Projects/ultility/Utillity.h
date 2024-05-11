#pragma once

struct Point
{
	float x, y;
};

struct Rect
{
	Point topLeft;
	Point bottomRight;
};


namespace SafeMemory
{
	template <class Type> void Delete(Type& t)
	{
		if (t)
		{
			delete t;
			t = nullptr;
		}
	}

	template <class Type> void Release(Type& t)
	{
		if (t)
		{
			t->Release();
			t = nullptr;
		}
	}
}