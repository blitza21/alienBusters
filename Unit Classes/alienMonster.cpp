#include "alienMonster.h"
#include "../game.h"
alienMonster::alienMonster(game* ptr, double p, double h, int cap , int tj , int id) : Unit(ptr, p, h, cap, tj , id)
{
	setType(AM);
}
bool alienMonster::attack(LinkedQueue<int> &amAttacked)
{
	int timestep;
	Unit* attackedUnit; //ET OR ES OR SU
	LinkedQueue<Unit*> &tempList = gamePtr->getEnemyList(type, attackCapacity, timestep);

	if (tempList.isEmpty())
		return false;

	while (tempList.dequeue(attackedUnit))
	{
		amAttacked.enqueue(attackedUnit->getID());
		attackedUnit->setTa(timestep);

		int per = gamePtr->getInputInfectedPer();
		int A = (rand() % 100) + 1;

		if (attackedUnit->getType() == ES && A <= per && ((earthSoldier*)attackedUnit)->getStatus() == NONINFECTED)
		{
			((earthSoldier*)attackedUnit)->setStatus(INFECTED);
			gamePtr->updateInfectedSoldiers(1);
			gamePtr->addUnit(attackedUnit, true);
			continue;
		}

		double damage = (power * health / 100) / sqrt(attackedUnit->getHealth());
		attackedUnit->setHealth(attackedUnit->getHealth() - damage);


		if (attackedUnit->getType() !=SU && attackedUnit->getHealth() > 0 && attackedUnit->getHealth() < 0.2 * initHealth)
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
			gamePtr->addUnit(attackedUnit , true);
		}
	}

	return true;
}