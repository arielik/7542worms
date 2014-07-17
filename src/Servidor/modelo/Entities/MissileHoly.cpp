#include "MissileHoly.h"


MissileHoly::MissileHoly(int id):Missile(id){
	//printf("\ncreating holy");
	this->withDelayedExplosion=true;
	this->weaponId=HOLY;
	this->explodeTime=HOLY_TIME;
	this->exploded = false;
	this->drowned = false;
}
