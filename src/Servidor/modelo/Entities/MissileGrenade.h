
#ifndef MISSILEGRENADE_H_
#define MISSILEGRENADE_H_
#include "Missile.h"
#include <iostream>

class MissileGrenade: public Missile{

	public:
		MissileGrenade();
		~MissileGrenade();
		MissileGrenade(int id);
};

#endif