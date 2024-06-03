#pragma once
#include "../DS/ArrayStack.h"
#include "../DS/priQueue.h"
#include "../DS/LinkedQueue.h"
#include "../Unit Classes/earthTank.h"
#include "../Unit Classes/earthGunnery.h"
#include"../Unit Classes/earthSoldier.h"
#include "../Unit Classes/healUnit.h"

class earthArmy
{
private:
	ArrayStack<earthTank*> EarthTanks;
	priQueue<earthGunnery*> EarthGunnery;
	LinkedQueue<earthSoldier*> EarthSoldiers;
	ArrayStack<healUnit*> HealList;

	int ETcount;
	int EGcount;
	int EScount;
	int HUcount;
	int infectedSoldiersCount;

public:
	earthArmy();

	bool attack(LinkedQueue<int> &esAttacked , LinkedQueue<int> &etAttacked , LinkedQueue<int> &egAttacked , LinkedQueue<int> & huHealed);

	void addEarthUnit(Unit* unit);		//Adds the unit passed to its appropriate container


	Unit* pickEarthUnit(unitType);
	Unit* removeEarthUnit(unitType);			//Removes a unit according to the unit type passed 

	void spreadInfection();
	void incrementInfected();
	void decrementInfected();

	int calcTotalInfected();
	void print();


	//Getters
	int getETcount();
	int getEGcount();
	int getEScount();
	int getHUcount();
	int getInfectedSoldiersCount();

	int getTotalInfectedSoldiersCount();


	~earthArmy();

};

