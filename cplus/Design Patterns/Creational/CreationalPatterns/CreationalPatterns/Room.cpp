#include "Room.h"

Room::Room(int id) : _id{ id }, _sides{ nullptr }
{
}

void Room::Enter()
{
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