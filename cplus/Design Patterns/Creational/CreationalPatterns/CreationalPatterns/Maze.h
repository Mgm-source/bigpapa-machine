#pragma once
#include "Room.h"
#include <vector>
class Maze {
	std::vector<Room*> _rooms;
public: 
	Maze() = default;
	void addRoom(Room* room);
	Room* RoomID(int id) const;
};