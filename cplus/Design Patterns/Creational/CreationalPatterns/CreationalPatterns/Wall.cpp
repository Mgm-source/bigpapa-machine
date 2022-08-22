#include "Wall.h"

void Wall::Enter()
{
}

Wall* Wall::Clone() const
{
	return new Wall(*this);
}

Wall::~Wall()
{
	std::cout << "Wall deleted \n";
}
