#pragma once
#include "MapSite.h"
#include "Room.h"

class Door : public MapSite { 
	bool _isOpen;
	int _id;
	Room* _front;
	Room* _back;
public:
	Door(int id ,Room* = nullptr, Room* = nullptr);
	int doorID() { return _id; }
	int frontID() { return _front ? _front->getID(): 0; };
	int BackID() { return _back ? _back->getID(): 0; };
	virtual void Enter();
	virtual void Initalise(Room* front, Room* back);
	virtual Door* Clone() const override;
	Room* connectedRoom(Room* room);
	~Door() { std::cout << "Door deleted \n"; }
};