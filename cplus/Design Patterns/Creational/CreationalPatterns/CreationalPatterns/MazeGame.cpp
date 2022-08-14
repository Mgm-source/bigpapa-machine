#include "MazeGame.h"
#include "Door.h"
#include "Wall.h"
#include "Room.h"

Maze MazeGame::CreateMaze()
{
    Maze maze;

    Room* room1 = new Room(1);
    Room* room2 = new Room(2);

    Door* door = new Door(room1, room2);

    room1->setSide(Direction::North, new Wall);
    room1->setSide(Direction::South, door);
    room1->setSide(Direction::West, new Wall);
    room1->setSide(Direction::East, new Wall);

    room2->setSide(Direction::North, new Wall);
    room2->setSide(Direction::West, door);
    room2->setSide(Direction::South, new Wall);
    room2->setSide(Direction::East, new Wall);

    maze.addRoom(room1);
    maze.addRoom(room2);

    door->Enter();

    return maze;
}

Maze MazeGame::CreateMaze(MazeFactory& factory)
{
    Maze maze = factory.MakeMaze();
    
    Room* front = factory.MakeRoom(1);
    Room* back = factory.MakeRoom(2);

    Door* door = factory.MakeDoor(front, back);

    front->setSide(Direction::North, factory.MakeWall());
    front->setSide(Direction::South, door);
    front->setSide(Direction::West, factory.MakeWall());
    front->setSide(Direction::East, factory.MakeWall());

    back->setSide(Direction::North, factory.MakeWall());
    back->setSide(Direction::West, door);
    back->setSide(Direction::South, factory.MakeWall()); 
    back->setSide(Direction::East, factory.MakeWall());

    maze.addRoom(front);
    maze.addRoom(back);

    return maze;
}
