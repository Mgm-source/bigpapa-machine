#pragma once
#include "MapSite.h"
class Room : public MapSite {
	std::vector<MapSite*> _sides;
	int _id;
public:
	Room(int id);
	virtual void Enter();
	virtual Room* Clone() const override;
	int getID() { return _id; };
	MapSite* getSide(Direction direction) const;
	void setSide(Direction direction, MapSite* component);
};