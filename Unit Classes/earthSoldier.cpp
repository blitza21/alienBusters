#include "earthSoldier.h"
#include "../game.h"
earthSoldier::earthSoldier(game* ptr, double p, double h, int cap , int tj , int id) : Unit(ptr, p, h, cap, tj , id)
{
	setType(ES);
	setStatus(NONINFECTED);
	timeStepsInUml = 0;
	isHealed = false;
}

bool earthSoldier::attack(LinkedQueue<int>& esAttacked)
{
	int timestep;
	LinkedQueue<Unit*> &tempList = gamePtr->getEnemyList(type, attackCapacity , timestep , status);

	if (tempList.isEmpty())
		return false;

	Unit* attackedUnit;	// AS OR ES (if infected)

	while (tempList.dequeue(attackedUnit))
	{
		if (this->getID() == attackedUnit->getID())	// Checks if es attacks itself
		{
			gamePtr->addUnit(attackedUnit, true);
			continue;
		}

		esAttacked.enqueue(attackedUnit->getID());
		attackedUnit->setTa(timestep);
		double damage = (power * health / 100) / sqrt(attackedUnit->getHealth());		// attack damage
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

int earthSoldier::getTimeStepsInUml()
{
	return timeStepsInUml;
}

void earthSoldier::setTimeStepsInUml(int ts)
{
	timeStepsInUml = ts;
}


void earthSoldier::setHealed(bool v)
{
	isHealed = v;
}

bool earthSoldier::IsHealed()
{
	return isHealed;
}

ESstatus earthSoldier::getStatus()
{
	return status;
}

void earthSoldier::setStatus(ESstatus s) 
{
	status = s;
}
