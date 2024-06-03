#pragma once
//this is a file for global constants..eg:the enum UnitType, max limit for lists, ...
//for any needed global constants we can declare them here
enum unitType
{
	ES,
	ET,
	EG,
	HU,
	AS,
	AM,
	AD,
	SU

};

enum tanksAttackMode	// EMERGENCY when es % falls below 30% of as ,and NORMAL when it reaches 80 % of as
{
	NORMAL, EMERGENCY
};
enum {MAX_EARTH_ID = 999 , MAX_ALIEN_ID = 2999 ,MAX_SAVER_ID=4250};

enum ESstatus {
	NONINFECTED,  //never been infected before
	INFECTED,	  //currently infected
	IMMUNE        //healed from infection and became immune
};