#include "CompostiteEquipment.h"

CompostiteEquipment::CompostiteEquipment(const char* name) : Equipment(name)
{
}

double CompostiteEquipment::netPrice()
{
	return 0.0;
}

double CompostiteEquipment::discountPrice()
{
	return 0.0;
}

void CompostiteEquipment::add(Equipment* equipment)
{
}

void CompostiteEquipment::remove(Equipment* equipment)
{
}

std::list<Equipment*> CompostiteEquipment::createList()
{
	return _equipment;
}