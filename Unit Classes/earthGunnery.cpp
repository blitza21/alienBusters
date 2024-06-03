#include "earthGunnery.h"
#include "../game.h"

earthGunnery::earthGunnery(game* ptr, double p, double h, int cap , int tj , int id) : Unit(ptr, p, h, cap, tj , id)
{
	setType(EG);
	calcPri();
}

bool earthGunnery::attack(LinkedQueue<int>& egAttacked)
{
	int timestep;
	LinkedQueue<Unit*> &tempList = gamePtr->getEnemyList(type, attackCapacity, timestep);

	if (tempList.isEmpty())
		return false;

	Unit* attackedUnit; //AD OR AM
	while (tempList.dequeue(attackedUnit))
	{
		egAttacked.enqueue(attackedUnit->getID());
		attackedUnit->setTa(timestep);
		double damage = (power * health / 100) / sqrt(attackedUnit->getHealth());

		attackedUnit->setHealth(attackedUnit->getHealth() - damage);
		if (attackedUnit->getHealth() <= 0)
		{
			attackedUnit->setTd(timestep);
			gamePtr->moveToKilledList(attackedUnit);
		}
		else
			gamePtr->addUnit(attackedUnit , true);
	}

	return true;
}

void earthGunnery::calcPri()
{
	priority = (health + power) / 2;		// just for now because the enqueue function needs a priority 
}

int earthGunnery::getPri()
{
	return priority;
}
