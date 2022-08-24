#pragma once
#include "MapSite.h"
class Door;

class Room : public MapSite {
	std::vector<MapSite*> _sides;
	int _id;
	bool _deleted;
public:
	Room(int id);
	Room(const Room&);
	Room(const Room&&) noexcept;
	virtual void Enter();
	virtual Room* Clone() const override;
	int getID() { return _id; };
	MapSite* getSide(Direction direction) const;
	void setSide(Direction direction, MapSite* component);
	void changeDoor(Door* door);
	~Room();
};