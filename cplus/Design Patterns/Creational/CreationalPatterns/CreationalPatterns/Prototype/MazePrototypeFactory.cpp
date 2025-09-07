#include "MazePrototypeFactory.h"

MazePrototypeFactory::MazePrototypeFactory(Maze* maze, Room* room, Door* door, Wall* wall):
    _prototypeMaze{ maze }, _prototypeRoom{ room }, _prototypeDoor{ door }, _prototypeWall{ wall }
{
}

Maze* MazePrototypeFactory::MakeMaze() const
{
    return _prototypeMaze->Clone();
}

Room* MazePrototypeFactory::MakeRoom(int id) const
{
    return _prototypeRoom->Clone();
}

Door* MazePrototypeFactory::MakeDoor(int id, Room* current, Room* next) const
{
   Door* door = _prototypeDoor->Clone();
   door->Initalise(current, next);
   return door;
}

Wall* MazePrototypeFactory::MakeWall() const
{
    return _prototypeWall->Clone();
}

