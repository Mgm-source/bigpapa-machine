#include "MazeGame.h"
#include "StandardMazeBuilder.h"

int main() 
{
	MazeGame mazeGame;
	//Maze maze = mazeGame.CreateMaze();
	auto factory = MazeFactory::Instance();
	StandardMazeBuilder builder;
	mazeGame.CreateMaze();
	mazeGame.CreateMaze(*factory);
	mazeGame.CreateMaze(builder);
	return 0;
} 