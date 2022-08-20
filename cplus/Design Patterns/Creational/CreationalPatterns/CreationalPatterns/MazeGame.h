#pragma once
#include "Maze.h"
#include "MazeFactory.h"
#include "MazeBuilder.h"
class MazeGame {
public:
	MazeGame() = default;
	Maze CreateMaze();
	Maze* CreateMaze(MazeFactory& factory);
	Maze* CreateMaze(MazeBuilder& builder);

	//	factory methods:

	virtual Maze* MakeMaze() const { return new Maze; };
	virtual Room* MakeRoom(int room) const { return new Room(room); };
	virtual Wall* MakeWall() const { return new Wall; };
	virtual Door* MakeDoor(Room* front, Room* back) const { return new Door(front, back); };
};

