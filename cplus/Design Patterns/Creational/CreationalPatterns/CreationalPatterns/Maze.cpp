#include "Maze.h"
#include "Door.h"

Maze::Maze() : _component{ std::vector<MapSite*>() }, _deleted{ false }
{

}

Maze::Maze(const Maze& maze) : _deleted{ false }
{
	for (auto i = 0u; i < maze._component.size(); i++)
	{
		_component.push_back(maze._component[i]->Clone());

	}

	for (auto i = 0u; i < _component.size(); i++)
	{
		if (auto door = dynamic_cast<Door*>(_component[i]))
		{
			auto front = RoomID(door->frontID());
			auto back = RoomID(door->BackID());

			door->Initalise(front, back);

			front->changeDoor(door);
			back->changeDoor(door);
		}
	}
}

Maze::Maze(const Maze&& maze) noexcept : _deleted {maze._deleted }
{
	for (auto i = 0u; i < maze._component.size(); i++) 
	{
		_component.push_back(maze._component[i]->Clone());

	}

	for (auto i = 0u; i < _component.size(); i++)
	{
		if (auto door = dynamic_cast<Door*>(_component[i]))
		{
			auto front = RoomID(door->frontID());
			auto back = RoomID(door->BackID());

			door->Initalise(front, back);

			front->changeDoor(door);
			back->changeDoor(door);
		}
	}
}

void Maze::addComponent(MapSite * component)
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
