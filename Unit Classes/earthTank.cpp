#include "earthTank.h"
#include "../game.h"

earthTank::earthTank(game* ptr, double p, double h, int cap , int tj , int id) : Unit(ptr , p , h, cap , tj , id)
{
	setType(ET);
	timeStepsInUml = 0;
	isHealed = false;
}

bool earthTank::attack(LinkedQueue<int>& etAttacked)
{
	int timestep;
	LinkedQueue<Unit*> &tempList = gamePtr->getEnemyList(type, attackCapacity, timestep);

	if (tempList.isEmpty())
		return false;

	Unit* attackedUnit; // AM OR AS(under certain condition)
	while (tempList.dequeue(attackedUnit))
	{
		etAttacked.enqueue(attackedUnit->getID());
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
int earthTank::getTimeStepsInUml()
{
	return timeStepsInUml;
}

void earthTank::setTimeStepsInUml(int ts)
{
	timeStepsInUml = ts;
}

void earthTank::setHealed(bool v)
{
	isHealed = v;
}

bool earthTank::IsHealed()
{
	return isHealed;
}
