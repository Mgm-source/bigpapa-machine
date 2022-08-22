#include "MazeGame.h"
#include "Door.h"
#include "Wall.h"
#include "Room.h"

Maze* MazeGame::CreateMaze()
{
    Maze* maze = MakeMaze();

    //Room* room1 = new Room(1);
    //Room* room2 = new Room(2);

    //Door* door = new Door(room1, room2);

    //room1->setSide(Direction::North, new Wall);
    //room1->setSide(Direction::South, door);
    //room1->setSide(Direction::West, new Wall);
    //room1->setSide(Direction::East, new Wall);

    //room2->setSide(Direction::North, new Wall);
    //room2->setSide(Direction::West, door);
    //room2->setSide(Direction::South, new Wall);
    //room2->setSide(Direction::East, new Wall);

    //maze.addRoom(room1);
    //maze.addRoom(room2);

    //door->Enter();

    Room* room1 = MakeRoom(1);
    Room* room2 = MakeRoom(2);

    Door* door = MakeDoor(room1, room2);

    room1->setSide(Direction::North, MakeWall());
    room1->setSide(Direction::South, door);
    room1->setSide(Direction::West, MakeWall());
    room1->setSide(Direction::East, MakeWall());

    room2->setSide(Direction::North, MakeWall());
    room2->setSide(Direction::West, door);
    room2->setSide(Direction::South, MakeWall());
    room2->setSide(Direction::East, MakeWall());

    maze->addComponent(room1);
    maze->addComponent(room2);
    maze->addComponent(door);

    return maze;
}

Maze* MazeGame::CreateMaze(MazeFactory& factory)
{
    Maze* maze = factory.MakeMaze();
    
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

    maze->addComponent(front);
    maze->addComponent(back);

    return maze;
}

Maze* MazeGame::CreateMaze(MazeBuilder& builder)
{
    builder.BuildRoom(1);
    builder.BuildRoom(2);

    builder.BuildDoor(1, 2);

    return builder.GetMaze();
}
