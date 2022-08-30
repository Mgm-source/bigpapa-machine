#pragma once
#include <list>
class Equipment {
	const char* _name;
protected:
	Equipment(const char* name);
public:
	virtual ~Equipment() = default;
	virtual double netPrice();
	virtual double discountPrice();
	virtual void add(Equipment* equipment);
	virtual void remove(Equipment* equipment);
	virtual std::list<Equipment*>* CreateList();
};

