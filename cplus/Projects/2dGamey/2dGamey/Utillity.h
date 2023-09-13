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
		float getX() { return position.x; };
		float getY() { return position.y; };
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

struct Vertex3    //Overloaded Vertex Structure
{
	Vertex3() : pos{ {},{},{} } {}

	Vertex3(float x, float y, float z = 0.0f)
		: pos(x, y, z) {}

	DirectX::XMFLOAT3 pos;

	Vertex3(const DirectX::XMFLOAT3& pos)
		: pos(pos)
	{
	}
};


struct Vertex4
{
	Vertex4() : colour{ {},{},{}, {} } {}

	Vertex4(float r, float g, float b, float a = 0.0f)
		: colour(r, g, b, a) {}

	DirectX::XMFLOAT4 colour;

	Vertex4(const DirectX::XMFLOAT4& colour)
		: colour(colour)
	{
	}
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