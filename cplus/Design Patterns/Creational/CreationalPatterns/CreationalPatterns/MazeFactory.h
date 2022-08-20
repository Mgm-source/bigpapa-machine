#pragma once
#include "Maze.h"
#include "Wall.h"
#include "Door.h"
class MazeFactory {
	static MazeFactory* _instance;
public:
	static MazeFactory* Instance();
	virtual Maze*  MakeMaze() const { return  new Maze; };
	virtual Room* MakeRoom(int id) const { return new Room(id); };
	virtual Wall* MakeWall() const { return new Wall; };
	virtual Door* MakeDoor(Room* front,Room* back) const { return new Door(front,back); };
protected:
	MazeFactory() = default;
};