#include "MazeGame.h"
#include "StandardMazeBuilder.h"

int main() 
{
	MazeGame mazeGame;
	//Maze maze = mazeGame.CreateMaze();
	MazeFactory factory;
	StandardMazeBuilder builder;
	mazeGame.CreateMaze();
	//mazeGame.CreateMaze(factory);
	//mazeGame.CreateMaze(builder);
	return 0;
}