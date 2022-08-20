#pragma once
#include "MapSite.h"
#include "Room.h"
class Door : public MapSite { 
	bool isOpen;
	struct rooms
	{
		Room* front;
		Room* back;
	} _room ;

public:
	Door(Room* = nullptr, Room* = nullptr);
	virtual void Enter();
	virtual void Initalise(Room* current, Room* next);
	virtual Door* Clone() const override;
	Room* connectedRoom(Room* room);
};