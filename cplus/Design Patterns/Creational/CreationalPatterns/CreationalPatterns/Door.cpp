#include "Door.h"
#include <utility>
Door::Door(Room* front, Room* back) : _room{ front, back }, isOpen{ false }
{
}

void Door::Enter()
{
    std::swap(_room.front, _room.back);
}

Room* Door::connectedRoom(Room* room)
{
    return nullptr;
}
