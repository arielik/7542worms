
#ifndef MISSILEBURRO_H_
#define MISSILEBURRO_H_
#include "Missile.h"
#include <iostream>

class MissileBurro: public Missile{

	public:
		MissileBurro();
		~MissileBurro();
		MissileBurro(int id);
};

#endif