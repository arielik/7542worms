
#ifndef MISSILEFACTORY_H_
#define MISSILEFACTORY_H_
#include "Missile.h"
#include "MissileBazooka.h"
#include "MissileGrenade.h"
#include "MissileAirStrike.h"
#include "MissileBanana.h"
#include "MissileBurro.h"
#include "MissileDynamite.h"
#include "MissileHoming.h"
#include "MissileHoly.h"
#include "MissileSheep.h"
#include "MissileSuicide.h"




#include "../../../utils/Util.h"
#include <iostream>

class MissileFactory{

private:
	MissileFactory();
	static MissileFactory* pInstance;
public:
	~MissileFactory();
	static MissileFactory* getInstance();
	Missile* getMissile(int weaponId, int elementId);

};

#endif