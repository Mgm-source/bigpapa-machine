#pragma once
#include "Maze.h"
#include "Factory/MazeFactory.h"
#include "Builder/MazeBuilder.h"
class MazeGame {
public:
	MazeGame() = default;
	~MazeGame() = default;
	Maze* CreateMaze();
	Maze* CreateMaze(MazeFactory& factory);
	Maze* CreateMaze(MazeBuilder& builder);
};

