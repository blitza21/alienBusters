#pragma once
#include"../globalConstants.h"
#include <iostream>
#include <cmath>
using namespace std;
//As a beginning so we can initially work on it, might add functions later
class game;
template< typename T>
class LinkedQueue;
class Unit
{
	friend ostream& operator <<(ostream& output, Unit* unit);

protected:

	int ID;
	unitType type;
	int Tj;
	int Ta;
	int Td;
	double health;
	double initHealth;
	double power;
	int attackCapacity;
	game* gamePtr;
	
public:
	Unit(game* ptr , double p , double h , int cap , int tj , int id);

	void setID(int);
	int getID() const;

	void setType(unitType);
	unitType getType() const;

	void setTj(int);
	int getTj() const;

	void setTa(int);
	int getTa();

	void setTd(int);
	int getTd();

	void setHealth(double);
	double getHealth() const;

	int getInitHealth() const;
	void setPower(double);
	double getPower() const;

	void setAttackCapacity(int);
	int getAttackCapacity() const;

	virtual bool attack(LinkedQueue<int>& esAttacked) = 0;


};