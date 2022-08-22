#pragma once
#include "MapSite.h"
class Room : public MapSite {
	std::vector<MapSite*> _sides;
	int _id;
	bool _deleted;
public:
	Room(int id);
	Room(const Room& room);
	virtual void Enter();
	virtual Room* Clone() const override;
	int getID() { return _id; };
	MapSite* getSide(Direction direction) const;
	void setSide(Direction direction, MapSite* component);
	~Room();
};