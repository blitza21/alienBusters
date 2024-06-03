#include "alienSoldier.h"
#include "../game.h"
alienSoldier::alienSoldier(game* ptr, double p, double h, int cap , int tj , int id) : Unit(ptr, p, h, cap, tj , id)
{
	setType(AS);
}

bool alienSoldier::attack(LinkedQueue<int> &asAttacked)
{
	int timestep;
	LinkedQueue<Unit*>& tempList = gamePtr->getEnemyList(type, attackCapacity, timestep);

	if (tempList.isEmpty())
		return false;

	Unit* attackedUnit;	// ES OR SU
	while (tempList.dequeue(attackedUnit))
	{
		asAttacked.enqueue(attackedUnit->getID());
		attackedUnit->setTa(timestep);
		double damage = (power * health / 100) / sqrt(attackedUnit->getHealth());

		attackedUnit->setHealth(attackedUnit->getHealth() - damage);
		if (attackedUnit->getType() == ES && attackedUnit->getHealth() > 0 && attackedUnit->getHealth() < 0.2 * initHealth)
		{
			gamePtr->moveToUML(attackedUnit);
		}
		else if (attackedUnit->getHealth() <= 0)
		{
			if (attackedUnit->getType() == ES && ((earthSoldier*)attackedUnit)->getStatus() == INFECTED)
				gamePtr->updateInfectedSoldiers(0);

			attackedUnit->setTd(timestep);
			gamePtr->moveToKilledList(attackedUnit);
		}
		else
		{
			gamePtr->addUnit(attackedUnit, true);
		}
	}
	return true;
}