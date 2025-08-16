#pragma once
#include "Maze.h"
#include "Wall.h"
#include "Door.h"
#include "MazeFactory.h"

class MazeFactoryImp : public MazeFactory{
public:
	virtual Maze* MakeMaze() const { return  new Maze; };
	virtual Room* MakeRoom(int id) const { return new Room(id); };
	virtual Wall* MakeWall() const { return new Wall; };
	virtual Door* MakeDoor(int id, Room* front, Room* back) const { return new Door(id, front, back); };
};