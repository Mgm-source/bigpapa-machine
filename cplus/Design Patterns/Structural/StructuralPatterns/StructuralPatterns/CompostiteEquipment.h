#pragma once
#include "Equipment.h"
class CompostiteEquipment : public Equipment {
	const char* _name;
	std::list<Equipment*> _equipment;
protected:
	CompostiteEquipment(const char* name);
public:
	virtual ~CompostiteEquipment() = default;
	virtual double netPrice();
	virtual double discountPrice();
	virtual void add(Equipment* equipment);
	virtual void remove(Equipment* equipment);
	virtual std::list<Equipment*>* CreateList();
};

