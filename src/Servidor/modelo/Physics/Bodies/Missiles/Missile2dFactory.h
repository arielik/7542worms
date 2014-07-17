
#ifndef MISSILE2DFACTORY_H_
#define MISSILE2DFACTORY_H_
#include "../../../GameElement.h"
#include "Missile2d.h"
#include "Missile2dBazooka.h"
#include "Missile2dGrenade.h"
#include "MissileAirStrike2d.h"
#include "MissileBanana2d.h"
#include "MissileBurro2d.h"
#include "MissileDynamite2d.h"
#include "MissileHoly2d.h"
#include "MissileHoming2d.h"
#include "MissileSheep2d.h"


#include "../../../../../utils/Util.h"
#include <iostream>

class Missile2dFactory{

private:
	Missile2dFactory();
	static Missile2dFactory* pInstance;
public:
	~Missile2dFactory();
	static Missile2dFactory* getInstance();
	Missile2d* getMissile(int weaponId,ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement);

};

#endif