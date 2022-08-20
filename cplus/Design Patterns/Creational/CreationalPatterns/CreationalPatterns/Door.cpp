#include "Door.h"
#include <utility>
Door::Door(Room* front, Room* back) : _room{ front, back }, isOpen{ false }
{
}

void Door::Enter()
{
    std::swap(_room.front, _room.back);
}

void Door::Initalise(Room* current, Room* next)
{
    _room = { current, next };
}

Door* Door::Clone() const
{
    return new Door(*this);
}

Room* Door::connectedRoom(Room* room)
{
    return nullptr;
}
