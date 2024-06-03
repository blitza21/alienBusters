#pragma once
#include "Unit.h"
class healUnit : public Unit
{
public:
	healUnit(game* ptr, double p, double h, int cap, int tj, int id);
	virtual bool attack(LinkedQueue<int>& huHealed);
};

