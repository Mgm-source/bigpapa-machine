#pragma once
#include "MazeFactory.h"
class MazePrototypeFactory : public MazeFactory {
	Maze* _prototypeMaze;
	Room* _prototypeRoom;
	Door* _prototypeDoor;
	Wall* _prototypeWall;
public:
	MazePrototypeFactory(Maze* maze, Room* room, Door* door, Wall* wall);

	Maze* MakeMaze() const override;
	Room* MakeRoom(int id) const override;
	Door* MakeDoor(Room* current,Room* next) const override;
	Wall* MakeWall() const override;
};

