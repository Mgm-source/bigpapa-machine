#pragma once
#include "MazeBuilder.h"

class StandardMazeBuilder : public MazeBuilder {
	Direction CommonWall(Room*, Room*);
	Maze* _currentMaze;
public:
	StandardMazeBuilder();
	void BuildRoom(int room) override;
	void BuildDoor( int currentRoom, int nextRoom) override;
	Maze* GetMaze() override;
};

