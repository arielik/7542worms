
#ifndef MISSILESHEEP_H_
#define MISSILESHEEP_H_
#include "Missile.h"
#include <iostream>

class MissileSheep: public Missile{

	public:
		MissileSheep();
		~MissileSheep();
		MissileSheep(int id);
};

#endif