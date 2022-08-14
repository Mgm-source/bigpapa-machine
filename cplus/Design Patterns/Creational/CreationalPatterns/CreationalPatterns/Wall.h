#pragma once
#include "MapSite.h"
class Wall : public MapSite
{
public:
	Wall() = default; 
	virtual void Enter();
};