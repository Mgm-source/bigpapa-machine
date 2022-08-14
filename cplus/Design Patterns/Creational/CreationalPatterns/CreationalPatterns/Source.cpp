#include "MazeGame.h"
int main() 
{
	MazeGame mazeGame;
	//Maze maze = mazeGame.CreateMaze();
	MazeFactory factory;
	Maze maze = mazeGame.CreateMaze(factory);
	return 0;
}