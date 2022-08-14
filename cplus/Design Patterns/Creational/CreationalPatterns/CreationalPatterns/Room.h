#pragma once
#include "MapSite.h"
class Room : public MapSite
{
	MapSite* _sides[4];
	int _num;
public:
	Room(int num);
	virtual void Enter();
	MapSite* getSide(Direction) const;
	void setSide(Direction, MapSite*);
};