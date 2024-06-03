#include "saverUnit.h"
#include "../game.h"

saverUnit::saverUnit(game* ptr, double p, double h, int cap, int tj, int id):Unit(ptr, p, h, cap, tj, id)
{
	setType(SU);
}

bool saverUnit::attack(LinkedQueue<int>& suAttacked)
{
	int timestep;
	LinkedQueue<Unit*>& tempList = gamePtr->getEnemyList(type, attackCapacity, timestep);

	if (tempList.isEmpty())
		return false;

	Unit* attackedUnit;	// AS

	while (tempList.dequeue(attackedUnit))
	{
		suAttacked.enqueue(attackedUnit->getID());
		attackedUnit->setTa(timestep);
		double damage = (power * health / 100) / sqrt(attackedUnit->getHealth());

		attackedUnit->setHealth(attackedUnit->getHealth() - damage);
		if (attackedUnit->getHealth() <= 0)
		{
			attackedUnit->setTd(timestep);
			gamePtr->moveToKilledList(attackedUnit);
		}
		else
			gamePtr->addUnit(attackedUnit, true);
	}
	return true;
}
