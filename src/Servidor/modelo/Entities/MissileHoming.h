
#ifndef MISSILEHOMING_H_
#define MISSILEHOMING_H_
#include "Missile.h"
#include <iostream>

class MissileHoming: public Missile{

	public:
		MissileHoming();
		~MissileHoming();
		MissileHoming(int id);
};

#endif