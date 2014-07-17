
#ifndef MISSILEAIRSTRIKE_H_
#define MISSILEAIRSTRIKE_H_
#include "Missile.h"
#include <iostream>

class MissileAirStrike: public Missile{

	public:
		MissileAirStrike();
		~MissileAirStrike();
		MissileAirStrike(int id);
};

#endif