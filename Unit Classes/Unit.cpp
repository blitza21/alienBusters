#include "Unit.h"
#include "../game.h"
ostream& operator <<(ostream& output, Unit* unit)
{
	if (unit)
	{
		if (unit->getType() == ES && ((earthSoldier*)unit)->getStatus() == INFECTED)
			output << "*" << unit->ID << "*";
		else
			output << unit->ID;
	}
	return output;
}

Unit::Unit(game* ptr ,double p , double h , int cap , int tj , int id)
{
	gamePtr = ptr;
	setPower(p);
	setHealth(h);
	initHealth = h;
	setAttackCapacity(cap);
	setTj(tj);
	setID(id);
	Ta = 0;		// set Ta initially to zero to be able to check if it the unit has been attacked before or not
	Td = 0;
}
void Unit::setID(int id)
{
	ID = id;
}
int Unit::getID() const
{
	return ID;
}

void Unit::setPower(double p)
{
	power = p;
}
int Unit::getInitHealth() const
{
	return initHealth;
}
double Unit::getPower() const
{
	return power;
}

void Unit::setHealth(double h)
{
	health = h;
}
double Unit::getHealth() const
{
	return health;
}

void Unit::setAttackCapacity(int a)
{
	attackCapacity = a;
}
int Unit::getAttackCapacity() const
{
	return attackCapacity;
}

void Unit::setTj(int tj)
{
	Tj = tj;
}
int Unit::getTj() const
{
	return Tj;
}

void Unit::setTa(int ta)
{
	if (Ta == 0)	// only set Ta if it's the first time being attacked
		Ta = ta;
}
int Unit::getTa()
{
	return Ta;
}

void Unit::setTd(int td)
{
	Td = td;
}
int Unit::getTd()
{
	return Td;
}

void Unit::setType(unitType t)
{
	type = t;
}
unitType Unit::getType() const
{
	return type;
}
