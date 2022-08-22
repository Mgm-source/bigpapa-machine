#include "StandardMazeBuilder.h"
#include "Wall.h"
#include "Door.h"

Direction StandardMazeBuilder::CommonWall(Room* front, Room* back)
{
	return Direction();
}

StandardMazeBuilder::StandardMazeBuilder() : _currentMaze { new Maze }
{

}

void StandardMazeBuilder::BuildRoom(int room)
{
	if (!_currentMaze->RoomID(room)) 
	{
		Room* newRoom = new Room(room);
		newRoom->setSide(Direction::North,new Wall);
		newRoom->setSide(Direction::South, new Wall);
		newRoom->setSide(Direction::West, new Wall);
		newRoom->setSide(Direction::East, new Wall);
		_currentMaze->addComponent(newRoom);
	}
	
}

void StandardMazeBuilder::BuildDoor(int currentRoom, int nextRoom)
{
	Room* r1 = _currentMaze->RoomID(currentRoom);
	Room* r2 = _currentMaze->RoomID(nextRoom);

	Door* door = new Door(r1, r2);

	r1->setSide(CommonWall(r1, r2), door);
	r2->setSide(CommonWall(r2, r1), door);
}

Maze* StandardMazeBuilder::GetMaze()
{
	return _currentMaze;
}
