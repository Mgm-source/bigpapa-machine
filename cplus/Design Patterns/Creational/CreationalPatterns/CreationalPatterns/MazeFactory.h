#pragma once
#include "../CreationalPatterns/Maze.h"
#include "../CreationalPatterns/Wall.h"
#include "../CreationalPatterns/Door.h"
class MazeFactory {
public:
	MazeFactory() = default;
	virtual Maze MakeMaze() const { return  Maze(); };
	virtual Room* MakeRoom(int id) const { return new Room(id); };
	virtual Wall* MakeWall() const { return new Wall; };
	virtual Door* MakeDoor(Room* front,Room* back) const { return new Door(front,back); };
};