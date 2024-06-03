#include "alienDrone.h"
#include "../game.h"
alienDrone::alienDrone(game* ptr, double p, double h, int cap, int tj, int id) : Unit(ptr, p, h, cap, tj, id)
{
	setType(AD);
}
bool alienDrone::attack(LinkedQueue<int> &adAttacked)
{
	int timestep;
	Unit* attackedUnit;//ET or EG
	LinkedQueue<Unit*> &tempList = gamePtr->getEnemyList(type, attackCapacity, timestep);

	if (tempList.isEmpty())
		return false;

	while (tempList.dequeue(attackedUnit))
	{
		adAttacked.enqueue(attackedUnit->getID());

		attackedUnit->setTa(timestep);
		double damage = (power * health / 100) / sqrt(attackedUnit->getHealth());
		
		attackedUnit->setHealth(attackedUnit->getHealth() - damage);

		if (attackedUnit->getType() == ET && attackedUnit->getHealth() > 0 && attackedUnit->getHealth() < 0.2 * initHealth)
		{
			gamePtr->moveToUML(attackedUnit);
		}
		else if (attackedUnit->getHealth() <= 0)
		{
			attackedUnit->setTd(timestep);
			gamePtr->moveToKilledList(attackedUnit);
		}
		else
		{
			gamePtr->addUnit(attackedUnit , true);
		}
	}

	return true;
}