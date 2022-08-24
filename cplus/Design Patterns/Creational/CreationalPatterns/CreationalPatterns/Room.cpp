#include "Room.h"
#include "Door.h"

Room::Room(int id) : _id{ id }, _sides{ std::vector<MapSite*>(4,nullptr) }, _deleted{ false }
{
}

Room::Room(const Room& room) : _id{ room._id }, _deleted{ room._deleted }
{
    for (auto i = 0u; i < room._sides.size(); i++)
    {
        if (!dynamic_cast<Door*>(room._sides[i]))
        {
            _sides.push_back( room._sides[i]->Clone());
        }
        else 
        {
            _sides.push_back(room._sides[i]);
        }
        
    }
}

Room::Room(const Room&& room) noexcept : _id { room._id }, _deleted { room._deleted }
{
    for (auto i = 0u; i < room._sides.size(); i++)
    {
        if (!dynamic_cast<Door*>(room._sides[i]))
        {
            _sides.push_back(room._sides[i]->Clone());
        }
        else
        {
            _sides.push_back(room._sides[i]);
        }
    }
}

void Room::Enter()
{
}


Room* Room::Clone() const
{
    return new Room(*this);
}

MapSite* Room::getSide(Direction direction) const
{
    switch (direction)
    {
    case (Direction::North):
        return _sides[0];
    case (Direction::South):
        return _sides[1];
    case (Direction::West):
        return  _sides[2];
    case (Direction::East):
        return _sides[3];
    }
    return nullptr;
}

void Room::setSide(Direction direction, MapSite* component)
{
    switch (direction) 
    {
    case (Direction::North):
        _sides[0] = component;
        return;
    case (Direction::South):
        _sides[1] = component;
        return;
    case (Direction::West):
        _sides[2] = component;
        return;
    case (Direction::East):
        _sides[3] = component;
        return;
    }
}

void Room::changeDoor(Door* newdoor)
{
    for (auto i = 0u; i < _sides.size(); i++) 
    {
        if (auto door = dynamic_cast<Door*>(_sides[i]))
        {
            if (newdoor->doorID() == door->doorID())
            {
                _sides[i] = newdoor;
            }
        }
    }
}

Room::~Room()
{
    for (auto side : _sides) 
    {
        if (side) 
        {
            if (!side->isDestroyed())
            {
                delete side;
            }
        }

    }
    std::cout << "Room deleted " << _id << std::endl;
}
