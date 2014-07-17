#include "MissileBurro.h"


MissileBurro::MissileBurro(int id):Missile(id){
	this->withDelayedExplosion=false;
	this->weaponId=BURRO;
	this->exploded = false;
	this->drowned = false;
}
