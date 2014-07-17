#include "MissileHoming.h"


MissileHoming::MissileHoming(int id):Missile(id){
	this->withDelayedExplosion=false;
	this->weaponId=HMISSILE;
	this->exploded = false;
	this->drowned = false;
}
