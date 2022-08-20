#pragma once
#include "MapSite.h"
class Wall : public MapSite {
public:
	virtual void Enter();
	Wall* Clone() const override;
};