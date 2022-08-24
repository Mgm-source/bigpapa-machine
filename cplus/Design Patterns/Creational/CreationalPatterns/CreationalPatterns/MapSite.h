#pragma once
#include <vector>
#include <iostream>
enum class Direction {North, South, East, West};
class MapSite {
	bool _deleted = false;
public:
	bool isDestroyed() const { return _deleted; }
	virtual void Enter() = 0;
	virtual MapSite* Clone() const = 0;
	virtual ~MapSite();
};