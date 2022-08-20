#pragma once
#include "Room.h"
class Maze {
	std::vector<Room*> _rooms;
public: 
	void addRoom(Room* room);
	Room* RoomID(int id) const;
	virtual Maze* Clone() const;
};