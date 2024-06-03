#pragma once
#include"Unit.h"
class alienDrone:public Unit
{

public:
	alienDrone(game* ptr, double p, double h, int cap , int tj , int id);
	virtual bool attack(LinkedQueue<int> &adAttacked);
};

