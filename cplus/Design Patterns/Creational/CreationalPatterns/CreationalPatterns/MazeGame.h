#pragma once
#include "Maze.h"
#include "../AbstractFactory/MazeFactory.h"
class MazeGame
{
public:
	MazeGame() = default;
	Maze CreateMaze();
	Maze CreateMaze(MazeFactory& factory);
};

