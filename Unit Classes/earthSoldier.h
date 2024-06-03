#pragma once
#include"Unit.h"
class earthSoldier :public Unit
{
private:
	int timeStepsInUml;
	bool isHealed;
	ESstatus status;
public:
	earthSoldier(game*ptr, double p, double h, int cap , int tj , int id);
	virtual bool attack(LinkedQueue<int>& esAttacked);

	int getTimeStepsInUml();
	void setTimeStepsInUml(int ts);

	void setHealed(bool);
	bool IsHealed();
	ESstatus getStatus();
	void setStatus(ESstatus s);
};

