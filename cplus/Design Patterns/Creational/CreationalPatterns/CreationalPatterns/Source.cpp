#include "MazeGame.h"
#include "StandardMazeBuilder.h"

int main() 
{
	
	//Maze maze = mazeGame.CreateMaze();
	auto factory = MazeFactory::Instance();
	//StandardMazeBuilder builder;
	
	{
		MazeGame mazeGame;
		auto a = mazeGame.CreateMaze();
		a->~Maze();
	}
	
	return 0;
} 