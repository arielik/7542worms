#include "MissileSuicide.h"


MissileSuicide::MissileSuicide(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=SUICIDE;
	this->explodeTime=1;
	this->exploded = false;
	this->drowned = false;
}
