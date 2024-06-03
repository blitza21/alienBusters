#include "randGen.h"
#include "game.h"
#include"./Unit Containers/alienArmy.h"
#include"./Unit Containers/earthArmy.h"
#include"./Unit Containers/alliedArmy.h"
randGen::randGen(game* gamePtr)
{
	this->gamePtr = gamePtr;
}

Unit* randGen::createUnit(unitType type,double p,double h, int cap , int timestep)
{
	int lastEarthID = gamePtr->getLastEarthID();
	int lastAlienID = gamePtr->getLastAlienID();
	int lastSaverID = gamePtr->getLastSaverID();
	Unit* newUnit;
	switch (type)
	{
		case ES:
		{
			newUnit = new earthSoldier(gamePtr, p, h, cap, timestep, lastEarthID);
			return newUnit;
		}
		case ET:
		{
			newUnit = new earthTank(gamePtr, p, h, cap, timestep, lastEarthID);
			return newUnit;
		}
		case EG:
		{
			newUnit = new earthGunnery(gamePtr, p, h, cap, timestep, lastEarthID);
			return newUnit;
		}
		case HU:
		{
			newUnit = new healUnit(gamePtr, p, h, cap, timestep, lastEarthID);
			return newUnit;
		}
		case AS:
		{
			newUnit = new alienSoldier(gamePtr, p, h, cap, timestep, lastAlienID);
			return newUnit;
		}
		case AM:
		{
			newUnit = new alienMonster(gamePtr, p, h, cap, timestep, lastAlienID);
			return newUnit;
		}
		case AD:
		{
			newUnit = new alienDrone(gamePtr, p, h, cap, timestep, lastAlienID);
			return newUnit;
		}
		case SU:
		{
			newUnit = new saverUnit(gamePtr, p, h, cap, timestep, lastSaverID);
			return newUnit;
		}
	}
}

void randGen::generate(int timestep)
{
	int A1 = (rand() % 100) + 1; //will use it also for saverUnits
	int A2 = (rand() % 100) + 1;
	double infectionPer = gamePtr->getCurrentInfectedPer();
	if (infectionPer >= threshold) //once threshold reached , generate untill infected = 0
	{
		gamePtr->setThresholdStatus(true);
	}
	if (infectionPer == 0)
	{
		gamePtr->setThresholdStatus(false); //stop gen
	}
	bool getThresholdStatus = gamePtr->getThresholdStatus();

	if (getThresholdStatus && A1 <= Prob)
	{
		for (int i = 0; i < N; i++)
		{
			double Saverpower = minSaverPower + rand() % (maxSaverPower - minSaverPower + 1);
			double Saverhealth = minSaverHealth + rand() % (maxSaverHealth - minSaverHealth + 1);
			int SaverattackCap = minSaverAttackCap + rand() % (maxSaverAttackCap - minSaverAttackCap + 1);

			int lastSaverID = gamePtr->getLastSaverID();

			if (lastSaverID > MAX_SAVER_ID)
			{
				break;
			}
			Unit* createdUnit = createUnit(SU, Saverpower, Saverhealth, SaverattackCap,timestep);
			gamePtr->addUnit(createdUnit, false);
		}
	}


	
	if (A1 <= Prob)
	{
		for (int i = 0; i < N; i++) //earth unit generation
		{

			int B = (rand() % 100) + 1;
			double Earthpower = minEarthPower + rand() % (maxEarthPower - minEarthPower + 1);
			double Earthhealth = minEarthHealth + rand() % (maxEarthHealth - minEarthHealth + 1);
			int EarthattackCap = minEarthAttackCap + rand() % (maxEarthAttackCap - minEarthAttackCap + 1);

			int lastEarthID = gamePtr->getLastEarthID();

			if (lastEarthID > MAX_EARTH_ID)
			{
				break;
			}
			if (B <= ESper)
			{
				Unit* createdUnit = createUnit(ES, Earthpower, Earthhealth, EarthattackCap, timestep);
				gamePtr->addUnit(createdUnit , false);
			}
			else if (B <= ESper + ETper)
			{
				Unit* createdUnit = createUnit(ET, Earthpower, Earthhealth, EarthattackCap, timestep);
				gamePtr->addUnit(createdUnit , false);
			}
			else if (B <= ESper + ETper + EGper)
			{
				Unit* createdUnit = createUnit(EG, Earthpower, Earthhealth, EarthattackCap, timestep);
				gamePtr->addUnit(createdUnit ,false);
			}
			else
			{
				Unit* createdUnit = createUnit(HU, Earthpower, Earthhealth, EarthattackCap, timestep);
				gamePtr->addUnit(createdUnit , false);
			}
		}
		
	}

	if (A2 <= Prob)
	{
		for (int i = 0; i < N; i++) //alien unit generation
		{
			int B = (rand() % 100) + 1;
			double Alienpower = minAliensPower + rand() % (maxAliensPower - minAliensPower + 1);
			double Alienhealth = minAliensHealth + rand() % (maxAliensHealth - minAliensHealth + 1);
			int AlienattackCap = minAliensAttackCap + rand() % (maxAliensAttackCap - minAliensAttackCap + 1);

			int lastAlienID = gamePtr->getLastAlienID();

			if (lastAlienID > MAX_ALIEN_ID)
			{
				break;
			}
			if (B <= ASper)
			{
				Unit* createdUnit = createUnit(AS, Alienpower, Alienhealth, AlienattackCap, timestep);
				gamePtr->addUnit(createdUnit, false);
			}
			else if (B <= ASper + AMper)
			{
				Unit* createdUnit = createUnit(AM, Alienpower, Alienhealth, AlienattackCap, timestep);
				gamePtr->addUnit(createdUnit, false);
			}
			else
			{
				Unit* createdUnit = createUnit(AD, Alienpower, Alienhealth, AlienattackCap, timestep);
				gamePtr->addUnit(createdUnit, false);
			}
		}
	}
}



void randGen::setN(int n)
{
	N = n;
}

void randGen::setES(int n)
{
	ESper = n;
}

void randGen::setET(int n)
{
	ETper = n;
}

void randGen::setEG(int n)
{
	EGper = n;
}

void randGen::setHU(int n)
{
	HUper = n;
}

void randGen::setAS(int n)
{
	ASper = n;
}

void randGen::setAM(int n)
{
	AMper = n;
}

void randGen::setAD(int n)
{
	ADper = n;
}

void randGen::setProb(int n)
{
	Prob = n;
}


void randGen::setMinEarthHealth(int n)
{
	minEarthHealth = n;
}

void randGen::setMaxEarthHealth(int n)
{
	maxEarthHealth = n;
}

void randGen::setMinEarthPower(int n)
{
	minEarthPower = n;
}

void randGen::setMaxEarthPower(int n)
{
	maxEarthPower = n;
}

void randGen::setMinEarthAttackCap(int n)
{
	minEarthAttackCap = n;
}

void randGen::setMaxEarthAttackCap(int n)
{
	maxEarthAttackCap = n;
}

void randGen::setMinAlienHealth(int n)
{
	minAliensHealth = n;
}

void randGen::setMaxAlienHealth(int n)
{
	maxAliensHealth = n;
}

void randGen::setMinAlienPower(int n)
{
	minAliensPower = n;
}

void randGen::setMaxAlienPower(int n)
{
	maxAliensPower = n;
}

void randGen::setMinAlienAttackCap(int n)
{
	minAliensAttackCap = n;
}

void randGen::setMaxAlienAttackCap(int n)
{
	maxAliensAttackCap = n;
}

void randGen::setThreshold(int n)
{
	threshold = n;
}

void randGen::setMinSaverPower(int n)
{
	minSaverPower = n;
}

void randGen::setMaxSaverPower(int n)
{
	maxSaverPower = n;
}

void randGen::setMinSaverHealth(int n)
{
	minSaverHealth = n;
}

void randGen::setMaxSaverHealth(int n)
{
	maxSaverHealth = n;
}

void randGen::setMinSaverAttackCap(int n)
{
	minSaverAttackCap = n;
}

void randGen::setMaxSaverAttackCap(int n)
{
	maxSaverAttackCap = n;
}
