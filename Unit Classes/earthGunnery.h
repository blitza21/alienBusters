#pragma once
#include "Unit.h"
class earthGunnery : public Unit
{
private:
	int priority;
public:
	earthGunnery(game* ptr, double p, double h, int cap , int tj , int id);
	virtual bool attack(LinkedQueue<int>& egAttacked);
	void calcPri();
	int getPri();
};

