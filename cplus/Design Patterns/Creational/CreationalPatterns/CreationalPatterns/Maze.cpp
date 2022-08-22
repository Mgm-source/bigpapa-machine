#include "Maze.h"

Maze::Maze() : _component{ std::vector<MapSite*>() }, _deleted{ false }
{

}

Maze::Maze(const Maze& maze) : _component{ maze._component }, _deleted { true }
{

}

Maze::Maze(const Maze&& maze) noexcept :  _component{ maze._component }, _deleted{ maze._deleted }
{

	for (size_t i = 0; i < maze._component.size(); i++)
	{
		_component[i] = maze._component[i]->Clone();
	}
}

void Maze::addComponent(MapSite* component)
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
	if (!_deleted) 
	{
		for (auto component : _component)
		{
			delete component;
		}
		_deleted = true;
	}

}
