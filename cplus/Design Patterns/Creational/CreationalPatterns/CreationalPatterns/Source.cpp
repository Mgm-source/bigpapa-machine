#include "MazeGame.h"
#include "StandardMazeBuilder.h"

int main() 
{
	
	//Maze maze = mazeGame.CreateMaze();
	auto factory = MazeFactory::Instance();
	//StandardMazeBuilder builder;
	
	//{
	//	MazeGame mazeGame;
	//	auto a = mazeGame.CreateMaze();
	//	a->~Maze();
	//}
	// destructor does not get called implictily when leaving the scope
	// default constructors are fine  

	auto a = []() {
		Maze a;
		Room* room1 = new Room(10);
		Room* room2 = new Room(20);

		Door* door = new Door(1 ,room1, room2);

		room1->setSide(Direction::North, new Wall);
		room1->setSide(Direction::South, door);
		room1->setSide(Direction::West, new Wall);
		room1->setSide(Direction::East, new Wall);

		room2->setSide(Direction::North, new Wall);
		room2->setSide(Direction::West, door);
		room2->setSide(Direction::South, new Wall);
		room2->setSide(Direction::East, new Wall);

		a.addComponent(room1);
		a.addComponent(room2);
		a.addComponent(door);
		return a;
	}();
	// destructor does get called implictily when leaving the scope
	// default constructors are not fine  

	return 0;
} 