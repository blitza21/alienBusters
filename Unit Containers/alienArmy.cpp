#include "alienArmy.h"

alienArmy::alienArmy()
{
	AScount = 0;
	AMcount = 0;
	ADcount = 0;
	droneToggle = true;
}

bool alienArmy::attack(LinkedQueue<int>& asAttacked, LinkedQueue<int>& amAttacked, LinkedQueue<int>& ad1Attacked , LinkedQueue<int>& ad2Attacked)
{
	bool c1 = false, c2 = false, c3 = false;

	Unit* as = pickAlienUnit(AS);
	if (as)
		c1 = as->attack(asAttacked);

	Unit* am =pickAlienUnit(AM);
	if (am)
		c2 = am->attack(amAttacked);

	Unit* ad1 = pickAlienUnit(AD);
	Unit* ad2 = pickAlienUnit(AD);
	if (ad1 != ad2) //more than one drone in the DEqueue
	{
		c3 = ad1->attack(ad1Attacked);
		ad2->attack(ad2Attacked);
	}

	return c1 || c2 || c3;
	
}

void alienArmy::Toggle()
{
	droneToggle = !droneToggle;
}

void alienArmy::addAlienUnit(Unit* unit)
{
	switch (unit->getType()) 
	{
		case AS:
		{
			alienSoldier* castedAS = dynamic_cast<alienSoldier*>(unit);
			AlienSoldiers.enqueue(castedAS);
			AScount++;
			break;
		}
		case AM:
		{
			alienMonster* castedAM = dynamic_cast<alienMonster*> (unit);
			AlienMonsters.add(castedAM);
			AMcount++;
			break;
		}
		case AD:
		{
			alienDrone* castedAD = dynamic_cast<alienDrone*>(unit);
			if (droneToggle)
				AlienDrones.enqueue(castedAD);
			else
				AlienDrones.enqueueFront(castedAD);
			ADcount++;
			Toggle();
			break;
		}
	}
}


Unit* alienArmy::pickAlienUnit(unitType unit)
{
	switch (unit)
	{
		case AS:
		{
			alienSoldier* as = NULL;
			AlienSoldiers.peek(as);
			return as;
		}

		case AD:
		{
			alienDrone* ad = NULL;
			if (droneToggle)
				AlienDrones.peek(ad);
			else
				AlienDrones.peekBack(ad);

			if (ad != NULL)
			{
				Toggle();
			}
			return ad;
		}

		case AM:
		{
			if (AMcount == 0)
				return NULL;


			int idx = rand() % AMcount;

			alienMonster* am = AlienMonsters[idx];
			return am;
		}
	}
}

Unit* alienArmy::removeAlienUnit(unitType unit)
{
	switch (unit)
	{
		case AS:
		{
			alienSoldier* as = NULL;
			if (AlienSoldiers.dequeue(as))
				AScount--;
			return as;
		}

		case AD:
		{
			alienDrone* ad = NULL;
			if (droneToggle)
				AlienDrones.dequeue(ad);
			else
				AlienDrones.dequeueBack(ad);

			if (ad != NULL)
			{
				ADcount--;
				Toggle();
			}
			return ad;
		}

		case AM:
		{
			if (AMcount == 0)
				return NULL;


			int idx = rand() % AMcount;

			alienMonster* am = AlienMonsters[idx];
			if (AlienMonsters.remove(idx));
				AMcount--;
			return am;
		}
	}
}


void alienArmy::print()  
{
	cout << "==============  Alien Army Alive Units =============" << endl;


	cout << AScount << " AS [";
	AlienSoldiers.print();
	cout << "]" << endl;


	cout << AMcount << " AM [";
	AlienMonsters.print();
	cout << "]" << endl;


	cout << ADcount << " AD [";
	AlienDrones.print();
	cout << "]" << endl;


}

int alienArmy::getAScount()
{
	return AScount;
}

int alienArmy::getAMcount()
{
	return AMcount;
}

int alienArmy::getADcount()
{
	return ADcount;
}


alienArmy::~alienArmy()
{
	for (int i = 0; i < AMcount; i++)
	{
		delete AlienMonsters[i];
		AlienMonsters[i] = NULL;
	}

	alienSoldier* as;
	while (AlienSoldiers.dequeue(as))
	{
		delete as;
		as = NULL;
	}

	alienDrone* ad;
	while (AlienDrones.dequeue(ad))
	{
		delete ad;
		ad = NULL;
	}
}