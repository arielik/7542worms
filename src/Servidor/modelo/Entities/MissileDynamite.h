
#ifndef MISSILEDYNAMITE_H_
#define MISSILEDYNAMITE_H_
#include "Missile.h"
#include <iostream>

class MissileDynamite: public Missile{

	public:
		MissileDynamite();
		~MissileDynamite();
		MissileDynamite(int id);
};

#endif