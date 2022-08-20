#pragma once
#include <vector>
enum class Direction {North, South, East, West};
class MapSite {
public:
	virtual void Enter() = 0;
	virtual MapSite* Clone() const = 0;
};