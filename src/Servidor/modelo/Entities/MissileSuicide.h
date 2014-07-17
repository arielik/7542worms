
#ifndef MISSILESUICIDE_H_
#define MISSILESUICIDE_H_
#include "Missile.h"
#include <iostream>

class MissileSuicide: public Missile{

	public:
		MissileSuicide();
		~MissileSuicide();
		MissileSuicide(int id);
};

#endif