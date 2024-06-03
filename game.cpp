#include "game.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;


game::game() : randGenObj(this)
{
	timestep = 1;
	killCount = 0;
	soldiersUMLCount = 0;
	tanksUMLCount = 0;
	successfullyHealedCount = 0;
	lastEarthID = 1;
	lastAlienID = 2000;
	lastSaverID = 4000;
	tanksMode = NORMAL;
	battleCondition = 0;
	thresholdStatus = false;
	loadParameters();
	readFileName();
	srand(time(0));
}

int game::getLastEarthID()
{
	return lastEarthID;
}

int game::getLastAlienID()
{
	return lastAlienID;
}

int game::getLastSaverID()
{
	return lastSaverID;
}

double game::getInputInfectedPer()
{
	return InputinfectionPer;
}

double game::getCurrentInfectedPer()
{
	int esCount = EarthArmy.getEScount();
	int infectedCount = EarthArmy.getInfectedSoldiersCount();
	if (esCount)
		return (((double)infectedCount / esCount) * 100);
	return 0;

}

bool game::getThresholdStatus()
{
	return thresholdStatus;
}

void game::setThresholdStatus(bool t)
{
	thresholdStatus = t;
}

void game::addUnit(Unit* unit , bool existingUnit)
{
	if (unit->getType() == SU)
	{
		AlliedArmy.addSaverUnit(unit);
		if (!existingUnit)
			lastSaverID++;
	}
	else if (unit->getType() == ES || unit->getType() == ET || unit->getType() == EG || unit->getType() == HU)
	{
		EarthArmy.addEarthUnit(unit);
		if (!existingUnit)
			lastEarthID++;
	}
	else
	{
		AlienArmy.addAlienUnit(unit);
		if (!existingUnit)
			lastAlienID++;
	}
}

void game::loadParameters()
{
	ifstream inputFile;
	inputFile.open("./Input_Files/weak_moderate.txt");

	if (inputFile.is_open())
	{

		int N, ES, ET, EG ,HU, AS, AM, AD, Prob, minEarthPower, maxEarthPower, minEarthHealth, maxEarthHealth, minEarthAttackCap, maxEarthAttackCap, minAliensPower, maxAliensPower, minAliensHealth, maxAliensHealth, minAliensAttackCap, maxAliensAttackCap , minSaverPower , maxSaverPower , minSaverHealth , maxSaverHealth , minSaverAttackCap , maxSaverAttackCap, thresholdPer;
		//int threshold
		inputFile >> N >> ES >> ET >> EG >> HU >> AS >> AM >> AD >> Prob >> InputinfectionPer >> thresholdPer;
		inputFile >> minEarthPower;
		inputFile.ignore();
		inputFile >> maxEarthPower;
		inputFile >> minEarthHealth;
		inputFile.ignore();
		inputFile >> maxEarthHealth;
		inputFile >> minEarthAttackCap;
		inputFile.ignore();
		inputFile >> maxEarthAttackCap;
		inputFile >> minAliensPower;
		inputFile.ignore();
		inputFile >> maxAliensPower;
		inputFile >> minAliensHealth;
		inputFile.ignore();
		inputFile >> maxAliensHealth;
		inputFile >> minAliensAttackCap;
		inputFile.ignore();
		inputFile >> maxAliensAttackCap;
		inputFile >> minSaverPower;
		inputFile.ignore();
		inputFile >> maxSaverPower;
		inputFile >> minSaverHealth;
		inputFile.ignore();
		inputFile >> maxSaverHealth;
		inputFile >> minSaverAttackCap;
		inputFile.ignore();
		inputFile >> maxSaverAttackCap;

		randGenObj.setN(N);
		randGenObj.setES(ES);
		randGenObj.setET(ET);
		randGenObj.setEG(EG);
		randGenObj.setHU(HU);
		randGenObj.setAS(AS);
		randGenObj.setAM(AM);
		randGenObj.setAD(AD);
		randGenObj.setProb(Prob);
		randGenObj.setThreshold(thresholdPer);
		randGenObj.setMinEarthPower(minEarthPower);
		randGenObj.setMaxEarthPower(maxEarthPower);

		randGenObj.setMinEarthHealth(minEarthHealth);
		randGenObj.setMaxEarthHealth(maxEarthHealth);

		randGenObj.setMinEarthAttackCap(minEarthAttackCap);
		randGenObj.setMaxEarthAttackCap(maxEarthAttackCap);

		randGenObj.setMinAlienPower(minAliensPower);
		randGenObj.setMaxAlienPower(maxAliensPower);

		randGenObj.setMinAlienHealth(minAliensHealth);
		randGenObj.setMaxAlienHealth(maxAliensHealth);

		randGenObj.setMinAlienAttackCap(minAliensAttackCap);
		randGenObj.setMaxAlienAttackCap(maxAliensAttackCap);


		randGenObj.setMinSaverHealth(minSaverHealth);
		randGenObj.setMaxSaverHealth(maxSaverHealth);

		randGenObj.setMinSaverPower(minSaverPower);
		randGenObj.setMaxSaverPower(maxSaverPower);

		randGenObj.setMinSaverAttackCap(minSaverAttackCap);
		randGenObj.setMaxSaverAttackCap(maxSaverAttackCap);


	}
	inputFile.close();
}

void game::readFileName()
{
	cout << "Enter output file name: ";
	cin >> outputFileName;
	cin.ignore();
}

void game::generateFile()
{
	ofstream output;
	output.open("./Output_Files/" + outputFileName + ".txt");

	if (output.fail()) {
		cout << "An error has occured while creating this file. Please try again!" << endl;
		return;
	}

	LinkedQueue<Unit*> tempList;
	Unit* unit;

	int killedESCount = 0, killedInfectedESCount = 0 , killedETCount = 0, killedEGCount = 0, killedASCount = 0, killedAMCount = 0, killedADCount = 0;

	double avgDfEarth = 0, avgDdEarth = 0, avgDbEarth = 0, avgDfAlien = 0, avgDdAlien = 0, avgDbAlien = 0;

	output << "Td	ID	  	Tj	Df	Dd	Db" << endl;

	while (KilledList.dequeue(unit)) {
		tempList.enqueue(unit);

		int Df = unit->getTa() - unit->getTj(); 
		int Dd = unit->getTd() - unit->getTa();  
		int Db = Df + Dd; 

		switch (unit->getType()) {
		case ES:
		{
			if(((earthSoldier*)unit)->getStatus() != NONINFECTED) killedInfectedESCount++;
			killedESCount++;
			avgDfEarth += Df;
			avgDdEarth += Dd;
			avgDbEarth += Db;
			break;
		}
		case ET:
			killedETCount++;
			avgDfEarth += Df;
			avgDdEarth += Dd;
			avgDbEarth += Db;
			break;
		case EG:
			killedEGCount++;
			avgDfEarth += Df;
			avgDdEarth += Dd;
			avgDbEarth += Db;
			break;
		case AS:
			killedASCount++;
			avgDfAlien += Df;
			avgDdAlien += Dd;
			avgDbAlien += Db;
			break;
		case AM:
			killedAMCount++;
			avgDfAlien += Df;
			avgDdAlien += Dd;
			avgDbAlien += Db;
			break;
		case AD:
			killedADCount++;
			avgDfAlien += Df;
			avgDdAlien += Dd;
			avgDbAlien += Db;
			break;
		default:
			break;
		}
		
		output << unit->getTd() << "\t" << unit->getID() << (unit->getID() < 1000 ? "\t\t" : "\t") << unit->getTj() << "\t" << Df << "\t" << Dd << "\t" << Db << endl;
	}

	output << endl;

	while (tempList.dequeue(unit))
		KilledList.enqueue(unit);


	double killedEarthCount = killedESCount + killedEGCount + killedETCount;
	double killedAlienCount = killedASCount + killedAMCount + killedADCount;

	if (killedEarthCount)
	{
		avgDfEarth /= killedEarthCount;
		avgDdEarth /= killedEarthCount;
		avgDbEarth /= killedEarthCount;
	}

	if (killedAlienCount)
	{
		avgDfAlien /= killedAlienCount;
		avgDdAlien /= killedAlienCount;
		avgDbAlien /= killedAlienCount;
	}


	int totalEarthAlive = EarthArmy.getEScount() + EarthArmy.getETcount() + EarthArmy.getEGcount();
	int totalEarth = killedEarthCount + totalEarthAlive;

	int totalInfectedSoldiers = EarthArmy.getTotalInfectedSoldiersCount() + killedInfectedESCount;

	int totalAlienAlive = AlienArmy.getAScount() + AlienArmy.getAMcount() + AlienArmy.getADcount();
	int totalAlien = killedAlienCount + totalAlienAlive; 


	output << "Battle Result: ";
	switch (battleCondition) {
	case 1:
		output << "Earth Army Wins!" << endl;
		break;
	case 2:
		output << "Alien Army Wins!" << endl;
		break;
	case 3:
		output << "Tie!" << endl;
		break;
	default:
		break;
	}

	

	output << "Battle went on for " << timestep - 1 << " timesteps!" << endl << endl;

	output << "Earth Army Stats: " << endl;

	output << "Total units (ES, ET, EG): " << EarthArmy.getEScount() + killedESCount << ", " << EarthArmy.getETcount() + killedETCount << ", " << EarthArmy.getEGcount() + killedEGCount  << endl;

	if (totalEarth)
	{
		output << "% of destructed units relative to total: (ES, ET, EG) ";
		output << ((EarthArmy.getEScount() + killedESCount) ? ((double)killedESCount / (EarthArmy.getEScount() + killedESCount)) * 100 : 0) << "%, ";
		output << ((EarthArmy.getETcount() + killedETCount) ? ((double)killedETCount / (EarthArmy.getETcount() + killedETCount)) * 100 : 0) << "%, ";
		output << ((EarthArmy.getEGcount() + killedEGCount) ? ((double)killedEGCount / (EarthArmy.getEGcount() + killedEGCount)) * 100 : 0) << "% \n";


		output << "% of total destructed units relative to total: ";
		output << (killedEarthCount / totalEarth) * 100 << "%" << endl;

		output << "% of total successfully healed units relative to total: ";
		output << ((double)successfullyHealedCount / totalEarth) * 100 << "%" << endl;

		output << "% of total infected Earth Soldiers relative to total: ";
		output << ((EarthArmy.getEScount() + killedESCount) ? ((double)totalInfectedSoldiers / (EarthArmy.getEScount() + killedESCount)) * 100 : 0) << "% \n";

		output << "Average Df, Dd, Db: " << avgDfEarth << ", " << avgDdEarth << ", " << avgDbEarth << endl;

		output << "Df/Db %: " << (avgDbEarth? (avgDfEarth / avgDbEarth) * 100 : 0) << "%" << endl;
		output << "Dd/Db %: " << (avgDbEarth ? (avgDdEarth / avgDbEarth) * 100 : 0) << "%" << endl << endl;
	}
	else
		output << "No more stats available for Earth Army units\n\n";


	output << "Alien Army Stats: " << endl;

	output << "Total units (AS, AM, AD): " << AlienArmy.getAScount() + killedASCount << ", " << AlienArmy.getAMcount() + killedAMCount << ", " << AlienArmy.getADcount() + killedADCount << endl;

	if (totalAlien)
	{
		output << "% of destructed units relative to total: (AS, AM, AD) ";

		output << ((AlienArmy .getAScount() + killedASCount) ? ((double)killedASCount / (AlienArmy.getAScount() + killedASCount)) * 100 : 0) << "%, ";
		output << ((AlienArmy .getAMcount() + killedAMCount) ? ((double)killedAMCount / (AlienArmy.getAMcount() + killedAMCount)) * 100 : 0) << "%, ";
		output << ((AlienArmy .getADcount() + killedADCount) ? ((double)killedADCount / (AlienArmy.getADcount() + killedADCount)) * 100 : 0) << "%  \n";

		output << "% of total destructed units relative to total: ";
		output << (killedAlienCount / totalAlien) * 100 << "%" << endl;

		output << "Average Df, Dd, Db: " << avgDfAlien << ", " << avgDdAlien << ", " << avgDbAlien << endl;

		output << "Df/Db %: " << (avgDbAlien? (avgDfAlien / avgDbAlien) * 100 : 0) << "%" << endl;
		output << "Dd/Db %: " << (avgDbAlien ? (avgDdAlien / avgDbAlien) * 100: 0) << "%" << endl;
	}
	else
		output << "No more stats available for Alien Army units\n\n";

	output.close();
}



void game::simulateGame(int mode)
{
	if (mode == 2) {
		cout << "Silent Mode\nSimulation Starts...\nSimulation Ends, Output file is created" << endl;
	}

	bool c1 = true, c2 = true;
	bool c = true; //for allied attack
	while (!battleCondition)
	{
		LinkedQueue<int> esAttacked;
		LinkedQueue<int> etAttacked;
		LinkedQueue<int> egAttacked;
		LinkedQueue<int> asAttacked;
		LinkedQueue<int> amAttacked;
		LinkedQueue<int> ad1Attacked;
		LinkedQueue<int> ad2Attacked;
		LinkedQueue<int> huHealed;
		LinkedQueue<int> suAttacked;

		randGenObj.generate(timestep);

		if (!thresholdStatus && AlliedArmy.getSUcount())
			AlliedArmy.withdraw();
		

		Unit* chosenES = EarthArmy.pickEarthUnit(ES);
		Unit* chosenET = EarthArmy.pickEarthUnit(ET);
		Unit* chosenEG = EarthArmy.pickEarthUnit(EG);
		Unit* chosenHU = EarthArmy.pickEarthUnit(HU);
		c1 = EarthArmy.attack(esAttacked , etAttacked , egAttacked , huHealed);

		Unit* chosenSU = AlliedArmy.pickSaverUnit();
		c = AlliedArmy.attack(suAttacked);

		Unit* chosenAS = AlienArmy.pickAlienUnit(AS);
		Unit* chosenAM = AlienArmy.pickAlienUnit(AM);
		Unit* chosenAD1 = AlienArmy.pickAlienUnit(AD);
		Unit* chosenAD2 = AlienArmy.pickAlienUnit(AD);
		c2 = AlienArmy.attack(asAttacked , amAttacked , ad1Attacked , ad2Attacked);

		EarthArmy.spreadInfection();
		if (mode == 1)
		{
			cout << endl << "Current timestep " << timestep << endl;
			EarthArmy.print();
			AlienArmy.print();
			AlliedArmy.print();

			cout << "==============  Units fighting at current timestep ============" << endl;

			if (chosenES && !esAttacked.isEmpty())
			{
				cout << "ES " << chosenES << " shot [";

				esAttacked.print();
				cout << "]" << endl;
			}
			if (chosenET && !etAttacked.isEmpty())
			{
				cout << "ET " << chosenET << " shot [";
				etAttacked.print();
				cout << "]" << endl;
			}
			if (chosenEG && !egAttacked.isEmpty())
			{
				cout << "EG " << chosenEG << " shot [";
				egAttacked.print();
				cout << "]" << endl;
			}
			if (chosenHU && !huHealed.isEmpty())
			{
				cout << "HU " << chosenHU << " healed [";
				huHealed.print();
				cout << "]" << endl;
			}
			if (chosenSU && !suAttacked.isEmpty())
			{
				cout << "SU " << chosenSU << " shot [";
				suAttacked.print();
				cout << "]" << endl;
			}
			if (chosenAS && !asAttacked.isEmpty())
			{
				cout << "AS " << chosenAS << " shot [";
				asAttacked.print();
				cout << "]" << endl;
			}

			if (chosenAM && !amAttacked.isEmpty())
			{
				cout << "AM " << chosenAM << " shot [";
				amAttacked.print();
				cout << "]" << endl;
			}
			
			if (chosenAD1 != chosenAD2 && !ad1Attacked.isEmpty() && !ad2Attacked.isEmpty())
			{
				cout << "AD " << chosenAD1 << " shot[";
				ad1Attacked.print();
				cout << "]" << endl;

				cout << "AD " << chosenAD2 << " shot[";
				ad2Attacked.print();
				cout << "]" << endl;
			}

			cout << "============== Soldiers UML Units ==============\n";
			soldiersUML.print();
			cout << endl;
			cout << "============== Tanks UML Units ==============\n";
			tanksUML.print();
			cout << endl;

			cout << "==============  Killed/Destructed Units ============" << endl;
			cout << killCount << " Killed units [";
			KilledList.print();
			cout << "]" << endl << endl;
			cout << "Press Enter to move to next timestep" << endl;


			string s;
			getline(cin, s);
		}
		checkUmlCondition();
		checkBattleEnd(c1, c2);
		timestep++;
	}

	generateFile();

	cout << "Battle has Ended!\nOutput file ( " << outputFileName << ".txt ) generated!" << endl;

}

void game::checkBattleEnd(bool c1 , bool c2) 
{

	if (timestep > 40)
	{
		bool alienWins = (EarthArmy.getEScount() + EarthArmy.getETcount() + EarthArmy.getEGcount() == 0) && (AlienArmy.getAScount() + AlienArmy.getAMcount() + AlienArmy.getADcount() != 0);
		bool zeroUnits = (EarthArmy.getEScount() + EarthArmy.getETcount() + EarthArmy.getEGcount() == 0) && (AlienArmy.getAScount() + AlienArmy.getAMcount() + AlienArmy.getADcount() == 0);
		bool earthWins = ((EarthArmy.getEScount() + EarthArmy.getETcount() + EarthArmy.getEGcount() + AlliedArmy.getSUcount() != 0) && (AlienArmy.getAScount() + AlienArmy.getAMcount() + AlienArmy.getADcount() == 0) || (zeroUnits && (soldiersUMLCount || tanksUMLCount)));
		
		if (alienWins)
			battleCondition = 2;	// Alien Army wins
			
		else if (earthWins)
			battleCondition = 1; // Earth Army wins

		else if (zeroUnits || (!c1 && !c2))
			battleCondition = 3;   // Tie

		earthSoldier* es;
		int pri;

		while (soldiersUML.dequeue(es, pri))
		{
			es->setHealth(0);
			es->setTd(timestep);
			moveToKilledList(es);
		}

		earthTank* et;
		while (tanksUML.dequeue(et))
		{
			et->setTd(timestep);
			et->setHealth(0);
			moveToKilledList(et);
		}

		soldiersUMLCount = 0;
		tanksUMLCount = 0;
	}
}


void game::moveToKilledList(Unit* unit)
{	
	KilledList.enqueue(unit);
	killCount++;
}

void game::moveToUML(Unit* unit)
{
	if (unit->getType() == ES)
	{
		if (((earthSoldier*)unit)->getStatus() == INFECTED)
			updateInfectedSoldiers(0);

		soldiersUML.enqueue((earthSoldier*)unit,unit->getInitHealth() - unit->getHealth());
		soldiersUMLCount++;
	}
	else
	{
		tanksUML.enqueue((earthTank*)unit);
		tanksUMLCount++;
	}
}

LinkedQueue<Unit*>& game::getEnemyList(unitType type ,  int attackCap, int& ts ,  ESstatus status)
{
	if (attackCap > 0)
	{
		ts = timestep;
		switch (type)
		{
			case SU:
			{
				Unit* as;
				int i = 0;
				do
				{
					as = AlienArmy.removeAlienUnit(AS);
					if (as)
					{
						EnemyList.enqueue(as);
						i++;
					}
				} while (i < attackCap && as);
				break;
			}
			case ES:
			{
				if (status == INFECTED)
				{
					if (EarthArmy.getEScount() == 1)	//only one earth soldier that is also infected . i.e will attack itself
						break;
					Unit* es;
					int i = 0;
					do
					{
						es = EarthArmy.removeEarthUnit(ES);
						if (es)
						{
							EnemyList.enqueue(es);
							i++;
						}
					} while (i < attackCap && es);
				}
				else
				{
					Unit* as;
					int i = 0;
					do
					{
						as = AlienArmy.removeAlienUnit(AS);
						if (as)
						{
							EnemyList.enqueue(as);
							i++;
						}
					} while (i < attackCap && as);
				}

				break;
			}
			case ET:
			{
				if (EarthArmy.getEScount() < 0.3 * AlienArmy.getAScount())
					tanksMode = EMERGENCY;

				if (EarthArmy.getEScount() >= 0.8 * AlienArmy.getAScount())
					tanksMode = NORMAL;

				if (tanksMode == EMERGENCY)		// Will attack alien soldiers as well as monsters 50-50
				{
					Unit* as, * am;
					int i = 0;
					do
					{
						as = AlienArmy.removeAlienUnit(AS);
						if (as)
						{
							EnemyList.enqueue(as);
							i++;
						}
					} while (i < attackCap / 2 && as);

					do
					{
						am = AlienArmy.removeAlienUnit(AM);
						if (am)
						{
							EnemyList.enqueue(am);
							i++;
						}
					} while (i < attackCap && am);
				}
				else
				{
					Unit* am;
					int i = 0;
					do
					{
						am = AlienArmy.removeAlienUnit(AM);
						if (am)
						{
							EnemyList.enqueue(am);
							i++;
						}
					} while (i < attackCap && am);

				}
				break;
			}
			case EG:
			{
				int i = 0;
				Unit* am, * ad1 , *ad2;
				do {
					am = AlienArmy.removeAlienUnit(AM);

					if (am)
					{
						EnemyList.enqueue(am);
						i++;
					}
				} while (i < attackCap / 2 && am);

				do
				{
					ad1 = AlienArmy.removeAlienUnit(AD);
					ad2 = AlienArmy.removeAlienUnit(AD);

					if (ad1)
					{
						EnemyList.enqueue(ad1);
						i++;
					}
					if (ad2)
					{
						EnemyList.enqueue(ad2);
						i++;
					}
				} while (i < attackCap && ad2);
				break;
			}
			case HU:
			{
				earthSoldier* es;
				int i = 0;
				do
				{
					es = NULL;
					int pri;
					if(soldiersUML.dequeue(es, pri))
					{
						soldiersUMLCount--;
						EnemyList.enqueue(es);
						i++;
					}
				} while (i < attackCap && es);

				if (i == attackCap)
					break;
				earthTank* et;
				do
				{
					et = NULL;
					if(tanksUML.dequeue(et))
					{
						tanksUMLCount--;
						EnemyList.enqueue(et);
						i++;
					}
				} while (i < attackCap && et);
				break;
			}
			case AS:
			{
				if (AlliedArmy.getSUcount())
				{
					Unit* es , * su;
					int i = 0;
					do
					{
						es = EarthArmy.removeEarthUnit(ES);
						if (es)
						{
							EnemyList.enqueue(es);
							i++;
						}
					} while (i < attackCap/2 && es);

					do
					{
						su = AlliedArmy.removeSaverUnit();
						if (su)
						{
							EnemyList.enqueue(su);
							i++;
						}
					} while (i < attackCap && su);
				}
				else
				{
					Unit* es;
					int i = 0;
					do
					{
						es = EarthArmy.removeEarthUnit(ES);
						if (es)
						{
							EnemyList.enqueue(es);
							i++;
						}
					} while (i < attackCap && es);
				}

				break;
			}
			case AM:
			{
				if (AlliedArmy.getSUcount())
				{
					Unit* et, * es , *su;
					int i = 0;
					do {
						et = EarthArmy.removeEarthUnit(ET);

						if (et)
						{
							EnemyList.enqueue(et);
							i++;
						}

					} while (i < attackCap / 3 && et);

					do
					{
						es = EarthArmy.removeEarthUnit(ES);

						if (es)
						{
							EnemyList.enqueue(es);
							i++;
						}

					} while (i < 2 *attackCap / 3 && es);

					do
					{
						su = AlliedArmy.removeSaverUnit();

						if (su)
						{
							EnemyList.enqueue(su);
							i++;
						}

					} while (i < attackCap  && su);
				}
				else
				{
					Unit* et, * es;
					int i = 0;
					do {
						et = EarthArmy.removeEarthUnit(ET);

						if (et)
						{
							EnemyList.enqueue(et);
							i++;
						}

					} while (i < attackCap / 2 && et);

					do
					{
						es = EarthArmy.removeEarthUnit(ES);

						if (es)
						{
							EnemyList.enqueue(es);
							i++;
						}

					} while (i < attackCap && es);
				}
				break;
			}
			case AD:
			{
				Unit* et, * eg;
				int i = 0;
				do {
					et = EarthArmy.removeEarthUnit(ET);

					if (et)
					{
						EnemyList.enqueue(et);
						i++;
					}

				} while (i < attackCap / 2 && et);

				do
				{
					eg = EarthArmy.removeEarthUnit(EG);

					if (eg)
					{
						EnemyList.enqueue(eg);
						i++;
					}

				} while (i < attackCap && eg);
				break;
			}
		}
	}
	return EnemyList;
}

void game::checkUmlCondition()
{
	earthSoldier* es;
	int pri;

	priQueue<earthSoldier*> soldiersTempQ;
	while (soldiersUML.dequeue(es , pri))
	{
		es->setTimeStepsInUml(es->getTimeStepsInUml() + 1);
		if (es->getTimeStepsInUml() >= 10) 
		{
			es->setTd(timestep);
			moveToKilledList(es);
			continue;
		}
		soldiersTempQ.enqueue(es , pri);
	}
	while (soldiersTempQ.dequeue(es, pri))
	{
		soldiersUML.enqueue(es, pri);
	}


	earthTank* et;
	LinkedQueue<earthTank*> tanksTempQ;
	while (tanksUML.dequeue(et))
	{
		et->setTimeStepsInUml(et->getTimeStepsInUml() + 1);
		if (et->getTimeStepsInUml() >= 10) 
		{
			et->setTd(timestep);
			moveToKilledList(et);
			continue;
		}
		tanksTempQ.enqueue(et);
	}
	while (tanksTempQ.dequeue(et))
	{
		tanksUML.enqueue(et);
	}
}

void game::incrementSuccessfullyHealed()
{
	successfullyHealedCount++;
}

void game::updateInfectedSoldiers(bool v)
{
	if (v)
		EarthArmy.incrementInfected();
	else
		EarthArmy.decrementInfected();
}



game::~game()
{
	Unit* unitToDelete;

	while (KilledList.dequeue(unitToDelete))
	{
		if (unitToDelete)
		{
			delete unitToDelete;
			unitToDelete = NULL;
		}
	}
}



