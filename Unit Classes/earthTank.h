#pragma once
#include "Unit.h"
class earthTank : public Unit
{
private:
	int timeStepsInUml;
	bool isHealed;
public:
	earthTank(game* ptr, double p, double h, int cap , int tj,  int id);
	virtual bool attack(LinkedQueue<int>& etAttacked);

	int getTimeStepsInUml();
	void setTimeStepsInUml(int ts);

	void setHealed(bool);
	bool IsHealed();
};

