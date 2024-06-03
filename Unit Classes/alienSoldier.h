#pragma once
#include "Unit.h"
class alienSoldier : public Unit
{
public:
	alienSoldier(game* ptr, double p, double h, int cap , int tj , int id);
	virtual bool attack(LinkedQueue<int> &asAttacked);
};

