#pragma once
#include "Unit Classes/Unit.h"

class game;
class randGen
{

	int N;  // the number of army units generated each timestep

	int ESper; // Earth Soldiers percentage
	int ETper; // Earth Tanks percentage
	int EGper; // Earth Gunnery percentage
	int HUper; // Heal Unit percentage
	int ASper; // Alien Soldiers percentage
	int AMper; // Alien Monsters percentage
	int ADper; // Alien Drones percentage

	int Prob; // probability to generate new army units
	int threshold;

	int minSaverPower;
	int maxSaverPower;

	int minSaverHealth;
	int maxSaverHealth;

	int minSaverAttackCap;
	int maxSaverAttackCap;

	int minEarthPower;
	int maxEarthPower;

	int minEarthHealth;									
	int maxEarthHealth;

	int minEarthAttackCap;						
	int maxEarthAttackCap;						
	
	int minAliensPower;								
	int maxAliensPower;	

	int minAliensHealth;								
	int maxAliensHealth;								

	int minAliensAttackCap;
	int maxAliensAttackCap;

	game* gamePtr;
	
public:
	randGen(game* gamePtr);

	void generate(int timestep);  
	Unit* createUnit(unitType type, double, double, int , int);

	// Setters
	void setN(int);
	void setES(int);
	void setET(int);
	void setEG(int);
	void setHU(int);
	void setAS(int);
	void setAM(int);
	void setAD(int);
	void setProb(int);
	void setMinEarthHealth(int);
	void setMaxEarthHealth(int);
	void setMinEarthPower(int);
	void setMaxEarthPower(int);
	void setMinEarthAttackCap(int);
	void setMaxEarthAttackCap(int);
	void setMinAlienHealth(int);
	void setMaxAlienHealth(int);
	void setMinAlienPower(int);
	void setMaxAlienPower(int);
	void setMinAlienAttackCap(int);
	void setMaxAlienAttackCap(int);



	void setThreshold(int n);

	void setMinSaverPower(int n);
	void setMaxSaverPower(int n);
	void setMinSaverHealth(int n);
	void setMaxSaverHealth(int n);
	void setMinSaverAttackCap(int n);
	void setMaxSaverAttackCap(int n);
	
}; 

