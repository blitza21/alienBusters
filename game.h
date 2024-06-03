#pragma once
#include"./Unit Containers/earthArmy.h"
#include"./Unit Containers/alienArmy.h"
#include"./Unit Containers/alliedArmy.h"
#include "randGen.h"
using namespace std;

class game
{
private:
	earthArmy EarthArmy;
	alienArmy AlienArmy;
	alliedArmy AlliedArmy;
	randGen randGenObj;

	LinkedQueue<Unit*> KilledList;
	LinkedQueue<Unit*> EnemyList;

	priQueue<earthSoldier*> soldiersUML;
	LinkedQueue<earthTank*> tanksUML;


	tanksAttackMode tanksMode;		// either NORMAL or EMERGENCY

	string outputFileName;
	
	int killCount;
	int soldiersUMLCount;
	int tanksUMLCount;
	int timestep;
	int lastEarthID;
	int lastAlienID;
	int lastSaverID;
	int battleCondition;
	int successfullyHealedCount;
	int InputinfectionPer;

	bool thresholdStatus;


	// Utility Functions

	void checkBattleEnd(bool c1, bool c2);
	void checkUmlCondition();	// Checks for units that spent more than 10 timesteps in UML
	void loadParameters();			//File loading function
	void readFileName();	// reads file name from user
	void generateFile();	// generates output file


public:

	game();

	void simulateGame(int mode);	//Main game function
	

	void addUnit(Unit* unit, bool existingUnit);

	void moveToKilledList(Unit* unit);
	void moveToUML(Unit* unit);
	LinkedQueue<Unit*> & getEnemyList(unitType type , int attackCap , int& ts , ESstatus status = NONINFECTED);

	void incrementSuccessfullyHealed();	
	void updateInfectedSoldiers(bool v);		// increments/decrements infected soldiers count

	int getLastEarthID();
	int getLastAlienID();
	int getLastSaverID();

	double getInputInfectedPer();
	double getCurrentInfectedPer();

	bool getThresholdStatus();
	void setThresholdStatus(bool t);
	~game();
};

