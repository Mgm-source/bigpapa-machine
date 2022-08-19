#pragma once
#include "Maze.h"
class MazeBuilder {
public: 
	virtual void BuildRoom(int room) {};
	virtual void BuildDoor(int currentRoom, int nextRoom) {};
	virtual Maze GetMaze() { return Maze(); };
protected:
	MazeBuilder() = default;
};