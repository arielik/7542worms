#include "MissileSheep.h"


MissileSheep::MissileSheep(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=SHEEP;
	this->explodeTime=SHEEP_TIME;
	this->exploded = false;
	this->grounded = 0;
	this->drowned = false;
}
