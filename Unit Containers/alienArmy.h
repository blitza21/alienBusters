#pragma once
#include "../DS/LinkedQueue.h"
#include"../DS/DEqueue.h"
#include "../DS/MonstersADT.h"
#include "../Unit Classes/alienSoldier.h"
#include "../Unit Classes/alienMonster.h"
#include"../Unit Classes/alienDrone.h"

class alienArmy 
{
private:
	LinkedQueue<alienSoldier*> AlienSoldiers;
	MonstersADT<alienMonster*> AlienMonsters;
	DEqueue<alienDrone*> AlienDrones;

	int AScount;
	int AMcount;
	int ADcount;
	bool droneToggle;

	void Toggle();					//Utility function to switch between front and rear when adding or removing drones

public:
	alienArmy();

	bool attack(LinkedQueue<int>& asAttacked, LinkedQueue<int>& amAttacked, LinkedQueue<int>& ad1Attacked , LinkedQueue<int>& ad2Attacked);

	void addAlienUnit(Unit* unit);		//Adds the unit passed to its appropriate container

	Unit* pickAlienUnit(unitType);
	Unit* removeAlienUnit(unitType);			//Removes a unit according to the unit type passed 

	void print();

	//Getters
	int getAScount();
	int getAMcount();
	int getADcount();
	
	~alienArmy();
};