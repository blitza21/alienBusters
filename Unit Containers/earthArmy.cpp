#include "earthArmy.h"
earthArmy::earthArmy()
{
	ETcount = 0;
	EGcount = 0;
	EScount = 0;
	HUcount = 0;
	infectedSoldiersCount = 0;
}

bool earthArmy::attack(LinkedQueue<int>& esAttacked, LinkedQueue<int>& etAttacked, LinkedQueue<int>& egAttacked ,LinkedQueue<int>& huHealed)
{
	bool c1 = false, c2 = false, c3 = false;
	Unit* es =pickEarthUnit(ES);
	if (es)
		c1 = es->attack(esAttacked);

	Unit* et = pickEarthUnit(ET);
	if (et)
		c2 = et->attack(etAttacked);

	Unit* eg= pickEarthUnit(EG);
	if (eg)
		c3 = eg->attack(egAttacked);

	Unit* hu = removeEarthUnit(HU);
	if (hu)
		hu->attack(huHealed);

	return c1 || c2 || c3;
}

void earthArmy::addEarthUnit(Unit* unit)
{
	switch (unit->getType())
	{
		case ES: 
		{
			earthSoldier* castedES = dynamic_cast<earthSoldier*>(unit);
			EarthSoldiers.enqueue(castedES);
			EScount++;
			break;
		}
		case ET: 
		{
			earthTank* castedET = dynamic_cast<earthTank*>(unit);
			EarthTanks.push(castedET);
			ETcount++;
			break;
		}
		case EG: 
		{
			earthGunnery* castedEG = dynamic_cast<earthGunnery*>(unit);
			EarthGunnery.enqueue(castedEG, castedEG->getPri());
			EGcount++;
			break;
		}
		case HU:
		{
			healUnit* castedHU = dynamic_cast<healUnit*>(unit);
			HealList.push(castedHU);
			HUcount++;
			break;
		}
	}
}


Unit* earthArmy::pickEarthUnit(unitType type)
{
	switch (type)
	{
		case ES:
		{
			earthSoldier* es = NULL;
			EarthSoldiers.peek(es);
			return es;
		}

		case ET:
		{
			earthTank* et = NULL;
			EarthTanks.peek(et);
			return et;
		}

		case EG:
		{
			earthGunnery* eg = NULL;
			int pri;
			EarthGunnery.peek(eg, pri);
			return eg;
		}

		case HU:
		{
			healUnit* hu = NULL;
			HealList.peek(hu);
			return hu;
		}
	}
}

Unit* earthArmy::removeEarthUnit(unitType type)
{
	switch (type)
	{
		case ES: 
		{
			earthSoldier* es = NULL;
			if (EarthSoldiers.dequeue(es))
				EScount--;
			return es;
		}

		case ET:
		{
			earthTank* et = NULL;
			if (EarthTanks.pop(et))
				ETcount--;
			return et;
		}

		case EG:
		{
			earthGunnery* eg = NULL;
			int pri;
			if (EarthGunnery.dequeue(eg, pri))
				EGcount--;
			return eg;
		}
		case HU:
		{
			healUnit* hu = NULL;
			if (HealList.pop(hu))
				HUcount--;
			return hu;
		}
	}
}




void earthArmy::spreadInfection()
{
	if (infectedSoldiersCount)
	{
		int prob = (rand() % 100) + 1;
		if (prob <= 2)
		{
			int idxToInfect = rand() % EScount;
			int idx = 0;

			LinkedQueue<earthSoldier*> tempList;
			earthSoldier* es;

			while (EarthSoldiers.dequeue(es))
			{
				if (idx == idxToInfect)
				{
					if (es->getStatus() == NONINFECTED)
					{
						es->setStatus(INFECTED);
						incrementInfected();
					}
					else 
						idxToInfect++;
				}
				tempList.enqueue(es);
				idx++;
			}

			while (tempList.dequeue(es))
				EarthSoldiers.enqueue(es);
		}
	}
}

void earthArmy::incrementInfected()
{
	infectedSoldiersCount++;
}

void earthArmy::decrementInfected()
{
	infectedSoldiersCount--;
	if (infectedSoldiersCount < 0)
		infectedSoldiersCount = 0;
}

int earthArmy::calcTotalInfected()
{
	LinkedQueue<earthSoldier*> tempList;
	earthSoldier* es;

	int totalInfected = 0;
	while (EarthSoldiers.dequeue(es))
	{
		tempList.enqueue(es);
		if (es->getStatus() != NONINFECTED)
			totalInfected++;
	}
	return totalInfected;
}
	


void earthArmy::print() {
	cout << "==============  Earth Army Alive Units =============" << endl;

	cout << (EScount ? ((double)infectedSoldiersCount / EScount) * 100 : 0) << "% of the ES are currently infected!" << endl;
	//cout << "Number of infected soldiers: " <<  infectedSoldiersCount << endl;
	cout << EScount << " ES [";
	EarthSoldiers.print();
	cout << "]" << endl;


	cout << ETcount << " ET [";
	EarthTanks.print();
	cout << "]" << endl;

	cout << EGcount << " EG [";
	EarthGunnery.print();
	cout << "]" << endl;

	cout << HUcount << " HU [";
	HealList.print();
	cout << "]" << endl;
}

int earthArmy::getETcount()
{
	return ETcount;
}

int earthArmy::getEGcount()
{
	return EGcount;
}

int earthArmy::getEScount()
{
	return EScount;
}

int earthArmy::getHUcount()
{
	return HUcount;
}

int earthArmy::getInfectedSoldiersCount()
{
	return infectedSoldiersCount;
}

int earthArmy::getTotalInfectedSoldiersCount()
{
	int count = 0;
	earthSoldier* es;

	LinkedQueue<earthSoldier*> tempList;
	while (EarthSoldiers.dequeue(es))
	{
		tempList.enqueue(es);
		if (es->getStatus() != NONINFECTED)
		{
			count++;
		}
	}

	while (tempList.dequeue(es))
		EarthSoldiers.enqueue(es);

	return count;
}


earthArmy::~earthArmy()
{

	earthSoldier* es;
	while (EarthSoldiers.dequeue(es))
	{
		delete es;
		es = NULL;
	}

	earthGunnery* eg;
	int pri;
	while (EarthGunnery.dequeue(eg, pri))
	{
		delete eg;
		eg = NULL;
	}

	earthTank* et;
	while (EarthTanks.pop(et))
	{
		delete et;
		et = NULL;
	}

	healUnit* hu;
	while (HealList.pop(hu))
	{
		delete hu;
		hu = NULL;
	}
}
