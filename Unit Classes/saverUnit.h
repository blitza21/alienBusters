#pragma once
#include"Unit.h"
class saverUnit:public Unit
{public:
	saverUnit(game* ptr, double p, double h, int cap, int tj, int id);
	virtual bool attack(LinkedQueue<int>& suAttacked);
};

