#include "MissileFactory.h"


MissileFactory* MissileFactory::pInstance = NULL;

MissileFactory* MissileFactory::getInstance(){

	if(pInstance == NULL){
		pInstance = new MissileFactory();
	}
	return pInstance;
}


MissileFactory::MissileFactory()
{

}

MissileFactory::~MissileFactory()
{

}

Missile* MissileFactory::getMissile(int weaponId, int elementId)
{
	Missile* aNewMissile;
	switch ( weaponId ){

	case BAZOOKA:
		aNewMissile = new MissileBazooka(elementId);
		break;
	case GRENADE:
		aNewMissile = new MissileGrenade(elementId);
		break;
	case BANANA:
		aNewMissile = new MissileBanana(elementId);
		break;
	case BURRO:
		aNewMissile = new MissileBurro(elementId);
		break;
	case HMISSILE:
		aNewMissile = new MissileHoming(elementId);
		break;
	case AIRATTACK:
		aNewMissile = new MissileAirStrike(elementId);
		break;
	case DYNAMITE:
		aNewMissile = new MissileDynamite(elementId);
		break;
	case HOLY:
		aNewMissile = new MissileHoly(elementId);
		break;
	case SHEEP:
		aNewMissile = new MissileSheep(elementId);
		break;
	case SUICIDE:
		aNewMissile = new MissileSuicide(elementId);
		break;
	case BANANITA:
		aNewMissile = new MissileBananita(elementId);
		break;
	default:
		aNewMissile = new MissileBazooka(elementId);
		break;
			
	}
	return aNewMissile;
}
