#include "MissileAirStrike.h"


MissileAirStrike::MissileAirStrike(int id):Missile(id){
	this->withDelayedExplosion=false;
	this->weaponId=AIRATTACK;
	this->explodeTime=0;
	this->exploded = false;
	this->drowned = false;
}
