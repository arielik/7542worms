#include "MissileBazooka.h"


MissileBazooka::MissileBazooka(int id):Missile(id){
	this->withDelayedExplosion=false;
	this->weaponId=BAZOOKA;
	this->explodeTime=0;
	this->exploded = false;
	this->drowned = false;
}
