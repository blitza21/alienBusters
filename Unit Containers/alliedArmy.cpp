#include "alliedArmy.h"

alliedArmy::alliedArmy()
{
	SUcount = 0;
}

bool alliedArmy::attack(LinkedQueue<int>& suAttacked)
{
	bool c = false;
	Unit* su = pickSaverUnit();
	if (su)
		c = su->attack(suAttacked);

	return c;
}

void alliedArmy::addSaverUnit(Unit* unit)
{
	saverUnit* castedSU = dynamic_cast<saverUnit*> (unit);
	SaverUnits.enqueue(castedSU);
	SUcount++;
}

Unit* alliedArmy::pickSaverUnit()
{
	saverUnit* su = NULL;
	SaverUnits.peek(su);
	return su;
}

Unit* alliedArmy::removeSaverUnit()
{
	saverUnit* su = NULL;
	if (SaverUnits.dequeue(su))
		SUcount--;
	return su;
}

void alliedArmy::withdraw()
{
	saverUnit* su;
	while (SaverUnits.dequeue(su))
	{
		delete su;
		su = NULL;
	}
	SUcount = 0;
}

void alliedArmy::print()
{
	cout << "==============  Allied Army Alive Units =============" << endl;


	cout << SUcount << " SU [";
	SaverUnits.print();
	cout << "]" << endl;
}

int alliedArmy::getSUcount()
{
	return SUcount;
}

alliedArmy::~alliedArmy()
{
	saverUnit* su;
	while (SaverUnits.dequeue(su))
	{
		delete su;
		su = NULL;
	}
}

