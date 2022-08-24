#include "Maze.h"
#include "Door.h"

Maze::Maze() : _component{ std::vector<MapSite*>() }, _deleted{ false }
{

}

void Maze::addDoor(Room* component)
{
	_component.push_back(component);
}

Room* Maze::RoomID(int id) const
{

	for (auto room : _component)
	{
		if (auto r = dynamic_cast<Room*>(room))
		{
			if (r->getID() == id)
			{
				return r;
			}
		}

	}

	return nullptr;
}

Maze* Maze::Clone() const
{
	return new Maze(*this);
}

Maze::~Maze()
{
	for (auto component : _component)
	{
		if (component)
		{
			if (!component->isDestroyed()) 
			{
				delete component;
			}
			
		}
		
	}
}
