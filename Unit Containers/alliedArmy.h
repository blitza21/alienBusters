#pragma once
#include "../DS/LinkedQueue.h"
#include "../Unit Classes/saverUnit.h"
class alliedArmy
{
private:
	LinkedQueue<saverUnit*>SaverUnits;
	int SUcount;

public:
	alliedArmy();

	bool attack(LinkedQueue<int>& suAttacked);

	void addSaverUnit(Unit* unit);		//Adds the unit passed to its appropriate container


	Unit* pickSaverUnit();
	Unit* removeSaverUnit();			//Removes a unit according to the unit type passed 

	void withdraw();
	void print();


	//Getters
	int getSUcount();

	~alliedArmy();
};

