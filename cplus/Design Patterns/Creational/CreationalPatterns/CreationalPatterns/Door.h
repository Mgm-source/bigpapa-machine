#pragma once
#include "MapSite.h"
#include "Room.h"
class Door : public MapSite
{
	struct 
	{
		Room* current;
		Room* next;
	} _room ;

	bool isOpen;

public:
	Door(Room* = nullptr, Room* = nullptr);
	virtual void Enter();
	Room* connectedRoom(Room* room);
};