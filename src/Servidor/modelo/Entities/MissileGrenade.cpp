#include "MissileGrenade.h"


MissileGrenade::MissileGrenade(int id):Missile(id){
	this->withDelayedExplosion=true;
	this->weaponId=GRENADE;
	this->explodeTime=GRENADE_TIME;
	this->exploded = false;
	this->drowned = false;
}
