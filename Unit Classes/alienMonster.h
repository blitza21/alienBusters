#pragma once
#include "Unit.h"
class alienMonster : public Unit
{
public:
	alienMonster(game* ptr, double p, double h, int cap , int tj , int id);
	virtual bool attack(LinkedQueue<int> &amAttacked);
};

