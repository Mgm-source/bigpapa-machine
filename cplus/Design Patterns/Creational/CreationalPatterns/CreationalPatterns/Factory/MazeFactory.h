#pragma once
#include "Maze.h"
#include "Wall.h"
#include "Door.h"
class MazeFactory {
public:
	static MazeFactory* instance();
	virtual Maze* MakeMaze() const = 0;
	virtual Room* MakeRoom(int id) const = 0;
	virtual Wall* MakeWall() const =0;
	virtual Door* MakeDoor(int id, Room* front, Room* back) const = 0;
protected:
	static MazeFactory* _instance;
	MazeFactory() = default;
};