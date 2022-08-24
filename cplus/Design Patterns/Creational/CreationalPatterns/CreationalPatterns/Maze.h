#pragma once
#include "Room.h"
class Maze {
	std::vector<MapSite*> _component;
	bool _deleted;
public: 
	Maze();
	void addDoor(Room* component);
	Room* RoomID(int id) const;
	virtual Maze* Clone() const;
	~Maze();
};