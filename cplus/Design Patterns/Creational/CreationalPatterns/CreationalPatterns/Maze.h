#pragma once
#include "Room.h"
class Maze {
	std::vector<MapSite*> _component;
	bool _deleted;
public: 
	Maze();
	Maze(const Maze& maze);
	Maze(const Maze&& maze) noexcept;
	void addComponent(MapSite * component);
	Room* RoomID(int id) const;
	virtual Maze* Clone() const;
	~Maze();
};