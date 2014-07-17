#include "Missile2d.h"

Missile2d::Missile2d()
{
}

Missile2d::Missile2d(ElementType type, float posX, float posY, float angle_x, float angle_y, float fuerzaDisparo, b2World *myWorld, GameElement *modelElement){

}

Missile2d::~Missile2d(){}



Explosion Missile2d::getExplosion()
{
	this->explosion.x=this->center.x;
	this->explosion.y=this->center.y;
	return this->explosion;
}