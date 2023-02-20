#pragma once

#include <d3d11.h>
#include <DirectXColors.h>
#pragma comment(lib, "d3d11.lib")

struct Point
{
	float x, y;
};

struct Rect
{
	Point topLeft;
	Point bottomRight;
};

namespace MOUSE
{

	enum MouseEvents
	{
		NONE = 0,
		LEFTDOWN =2,
		LEFTUP = 4,
		RIGHTDOWN = 8,
		RIGHTUP = 16
	};

	struct State
	{
		Point position;
		const int& getX() { return position.x; };
		const int& getY() { return position.y; };
		UINT event;
		bool isRightButtonDown() { return event & MouseEvents::RIGHTDOWN;}
		bool isLeftButtonDown() { return event & MouseEvents::LEFTDOWN; };
		bool isRightButtonClicked()
		{
			if (event & MouseEvents::RIGHTDOWN && event & MouseEvents::RIGHTUP)
			{
				event = MouseEvents::NONE;
				return true;
			}
			return false; 
		};

		bool isLeftButtonClicked()
		{
			if (event & MouseEvents::LEFTDOWN && event & MouseEvents::LEFTUP)
			{
				event = MouseEvents::NONE;
				return true;
			}
			return false;
		};
	};
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