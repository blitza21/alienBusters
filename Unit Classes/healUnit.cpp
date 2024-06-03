#include "healUnit.h"
#include "../game.h"
healUnit::healUnit(game* ptr, double p, double h, int cap, int tj, int id) : Unit(ptr, p, h, cap, tj, id)
{
	setType(HU);
}

bool healUnit::attack(LinkedQueue<int>& huHealed)
{
	int timestep;
	LinkedQueue<Unit*>& tempList = gamePtr->getEnemyList(type, attackCapacity, timestep);

	if (tempList.isEmpty())
	{
		gamePtr->addUnit(this , true);
		return false;
	}

	Unit* healedUnit; // ES OR ET
	while (tempList.dequeue(healedUnit))
	{
		huHealed.enqueue(healedUnit->getID());

		double healthImprov = (power * health / 100) / sqrt(healedUnit->getHealth());

		if (healedUnit->getType() == ES && ((earthSoldier*)healedUnit)->getStatus() == INFECTED)
			healedUnit->setHealth(healedUnit->getHealth() + healthImprov/2);
		else
			healedUnit->setHealth(healedUnit->getHealth() + healthImprov);

		if (healedUnit->getHealth() > 0.2 * initHealth)
		{
			gamePtr->addUnit(healedUnit, true);

			if (healedUnit->getType() == ES)
			{
				earthSoldier* healedSoldier = (earthSoldier*)healedUnit;
				healedSoldier->setTimeStepsInUml(0);

				if (healedSoldier->getStatus() == INFECTED)			
				{
					healedSoldier->setStatus(IMMUNE);
				}

				if (healedSoldier->IsHealed() == false)
				{
					gamePtr->incrementSuccessfullyHealed();
					healedSoldier->setHealed(true);
				}
			}
			else
			{
				earthTank* healedTank = (earthTank*)healedUnit;
				healedTank->setTimeStepsInUml(0);

				if (healedTank->IsHealed() == false)
				{
					gamePtr->incrementSuccessfullyHealed();
					healedTank->setHealed(true);
				}
			}
				
		}
		else
		{
			gamePtr->moveToUML(healedUnit);
		}
	}
	
	//Delete the HU after healing
	this->setHealth(0);
	gamePtr->moveToKilledList(this);
	this->setTa(timestep);
	this->setTd(timestep);
	return true;
}
