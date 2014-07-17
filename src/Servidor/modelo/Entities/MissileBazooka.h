
#ifndef MISSILEBAZOOKA_H_
#define MISSILEBAZOOKA_H_
#include "Missile.h"
#include <iostream>

class MissileBazooka: public Missile{

	public:
		MissileBazooka();
		~MissileBazooka();
		MissileBazooka(int id);
};

#endif