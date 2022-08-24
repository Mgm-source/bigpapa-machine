#include "Door.h"
#include <utility>

Door::Door(int id, Room* front, Room* back) : _id{ id }, _front{ front }, _back{ back }, _isOpen{ false }
{
}

void Door::Enter()
{
    std::swap(_front, _back);
}

void Door::Initalise(Room* front, Room* back)
{
    _front = front;
    _back = back;
}

Door* Door::Clone() const
{
    return new Door(*this);
}

Room* Door::connectedRoom(Room* room)
{
    return nullptr;
}
