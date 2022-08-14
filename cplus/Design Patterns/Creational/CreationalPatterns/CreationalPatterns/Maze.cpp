#include "Maze.h"

void Maze::addRoom(Room* room)
{
	_rooms.push_back(room);
}

Room* Maze::RoomID(int id) const
{

	for (auto r : _rooms)
	{
		if (r->getID() == id)
		{
			return r;
		}
	}

	return nullptr;
}
