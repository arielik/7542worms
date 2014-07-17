#include "MissileDynamite.h"


MissileDynamite::MissileDynamite(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=DYNAMITE;
	this->explodeTime=DYNAMITE_TIME;
	this->exploded = false;
	this->drowned = false;
}
