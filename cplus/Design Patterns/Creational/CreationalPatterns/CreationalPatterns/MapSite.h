#pragma once
enum class Direction {North, South, East, West};
class MapSite 
{
public:
	virtual void Enter() = 0;
};