#pragma once
#include "MapSite.h"
class Room : public MapSite {
	MapSite* _sides[4];
	int _id;
public:
	Room(int id);
	virtual void Enter();
	int getID() { return _id; };
	MapSite* getSide(Direction direction) const;
	void setSide(Direction direction, MapSite* component);
	~Room() = default;
};