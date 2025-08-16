#pragma once
#include "Equipment.h"
class CompostiteEquipment : public Equipment {
	std::list<Equipment*> _equipment;
protected:
	CompostiteEquipment(const char* name);
public:
	~CompostiteEquipment() = default;
	double netPrice() override;
	double discountPrice() override;
	void add(Equipment* equipment) override;
	void remove(Equipment* equipment) override;
	virtual		std::list<Equipment*> createList();
};

