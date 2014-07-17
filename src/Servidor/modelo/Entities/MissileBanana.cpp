#include "MissileBanana.h"


MissileBanana::MissileBanana(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=BANANA;
	this->explodeTime=BANANA_TIME;
	this->exploded = false;
	this->drowned = false;
}


MissileBananita::MissileBananita(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=BANANITA;
	this->explodeTime=BANANITA_TIME;
	this->exploded = false;
	this->drowned = false;
}