
#ifndef MISSILEHOLY_H_
#define MISSILEHOLY_H_
#include "Missile.h"
#include <iostream>

class MissileHoly: public Missile{

	public:
		MissileHoly();
		~MissileHoly();
		MissileHoly(int id);
};

#endif